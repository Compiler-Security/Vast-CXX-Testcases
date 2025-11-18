// RUN: %driver -cc1 %isys -std=c++11 -fmerge-all-constants %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -DNO_TLS -fmerge-all-constants %s %target -o %t%output-suffix && %filecheck

namespace std {
  typedef decltype(sizeof(int)) size_t;

  template <class _E>
  class initializer_list
  {
    const _E* __begin_;
    size_t    __size_;

    initializer_list(const _E* __b, size_t __s)
      : __begin_(__b),
        __size_(__s)
    {}

  public:
    typedef _E        value_type;
    typedef const _E& reference;
    typedef const _E& const_reference;
    typedef size_t    size_type;

    typedef const _E* iterator;
    typedef const _E* const_iterator;

    initializer_list() : __begin_(nullptr), __size_(0) {}

    size_t    size()  const {return __size_;}
    const _E* begin() const {return __begin_;}
    const _E* end()   const {return __begin_ + __size_;}
  };
}

struct destroyme1 {
  ~destroyme1();
};
struct destroyme2 {
  ~destroyme2();
};
struct witharg1 {
  witharg1(const destroyme1&);
  ~witharg1();
};
struct wantslist1 {
  wantslist1(std::initializer_list<destroyme1>);
  ~wantslist1();
};
std::initializer_list<int> globalInitList1 = {1, 2, 3};

#ifndef NO_TLS
namespace thread_local_global_array {
std::initializer_list<int> thread_local x = {1, 2, 3, 4};
}
#endif






std::initializer_list<witharg1> globalInitList2 = {
  witharg1(destroyme1()), witharg1(destroyme1())
};

void fn1(int i) {
  std::initializer_list<int> intlist{1, 2, i};
}

void fn2() {
  void target(std::initializer_list<destroyme1>);
  target({ destroyme1(), destroyme1() });
  destroyme2 dm2;
}

void fn3() {
  auto list = { destroyme1(), destroyme1() };
  destroyme2 dm2;
}

void fn4() {
  void target(std::initializer_list<witharg1>);
  target({ witharg1(destroyme1()), witharg1(destroyme1()) });
  destroyme2 dm2;
}

void fn5() {
  auto list = { witharg1(destroyme1()), witharg1(destroyme1()) };
  destroyme2 dm2;
}

void fn6() {
  void target(const wantslist1&);
  target({ destroyme1(), destroyme1() });
  destroyme2 dm2;
}
void fn7() {
  wantslist1 wl = { destroyme1(), destroyme1() };
  destroyme2 dm2;
}

void fn8() {
  void target(std::initializer_list<std::initializer_list<destroyme1>>);
  std::initializer_list<destroyme1> inner;
  target({ inner, { destroyme1() } });
  destroyme2 dm2;
}

void fn9() {
  std::initializer_list<destroyme1> inner;
  std::initializer_list<std::initializer_list<destroyme1>> list =
      { inner, { destroyme1() } };
  destroyme2 dm2;
}

void fn10(int i) {
  (void) new std::initializer_list<int> {i, 2, 3};
}

void fn11() {
  (void) new std::initializer_list<destroyme1> {destroyme1(), destroyme1()};
  destroyme2 dm2;
}

namespace PR12178 {
  struct string {
    string(int);
    ~string();
  };

  struct pair {
    string a;
    int b;
  };

  struct map {
    map(std::initializer_list<pair>);
  };

  map m{ {1, 2}, {3, 4} };
}

namespace rdar13325066 {
  struct X { ~X(); };

  void loop(X &x1, X &x2) {
    for (X x : { x1, x2 }) { }
  }
}

namespace dtors {
  struct S {
    S();
    ~S();
  };
  void z();

  void f() {
    std::initializer_list<S>{ S(), S() };


    z();

  }

  void g() {
    auto x = std::initializer_list<S>{ S(), S() };


    z();

  }

  void h() {
    std::initializer_list<S> x = { S(), S() };


    z();

  }
}

namespace partly_constant {
  int k;
  std::initializer_list<std::initializer_list<int>> &&il = { { 1, 2, 3 }, { 4, k }, { 5, 6, 7, 8 } };
}
namespace nested {
  struct A { A(); ~A(); };
  struct B { const A &a; ~B(); };
  struct C { std::initializer_list<B> b; ~C(); };
  void f();
  void g() {
    const C &c { { { A() }, { A() } } };

    f();



  }
}

namespace DR1070 {
  struct A {
    A(std::initializer_list<int>);
  };
  struct B {
    int i;
    A a;
  };
  B b = {1};
  struct C {
    std::initializer_list<int> a;
    B b;
    std::initializer_list<double> c;
  };
  C c = {};
}

namespace ArrayOfInitList {
  struct S {
    S(std::initializer_list<int>);
  };
  S x[1] = {};
}

namespace PR20445 {
  struct vector { vector(std::initializer_list<int>); };
  struct MyClass { explicit MyClass(const vector &v); };
  template<int x> void f() { new MyClass({42, 43}); }
  template void f<0>();
}

namespace ConstExpr {
  class C {
    int x;
  public:
    constexpr C(int x) : x(x) {}
  };
  void f(std::initializer_list<C>);
  void g() {
    f({C(1), C(2), C(3)});
  }
}

namespace B19773010 {
  template <class T1, class T2> struct pair {
    T1 first;
    T2 second;
    constexpr pair() : first(), second() {}
    constexpr pair(T1 a, T2 b) : first(a), second(b) {}
  };

  enum E { ENUM_CONSTANT };
  struct testcase {
    testcase(std::initializer_list<pair<const char *, E>>);
  };
  void f1() {
    testcase a{{"", ENUM_CONSTANT}};
  }
  void f2() {
    static std::initializer_list<pair<const char *, E>> a, p[2] =
        {a, {{"", ENUM_CONSTANT}}};
  }

  void PR22940_helper(const pair<void*, int>&) { }
  void PR22940() {
    PR22940_helper(pair<void*, int>());
  }
}
