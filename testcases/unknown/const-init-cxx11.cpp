// RUN: %driver -cc1 %isys -w -fmerge-all-constants %s -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -w -fmerge-all-constants %s -std=c++20 %target -o %t%output-suffix && %filecheck

namespace StructUnion {
  struct A {
    int n;
    double d;
    union U {
      constexpr U(int x) : x(x) {}
      constexpr U(const char *y) : y(y) {}
      int x;
      const char *y;
    } u;

    constexpr A(int n, double d, int x) : n(n), d(d), u(x) {}
    constexpr A(int n, double d, const char *y) : n(n), d(d), u(y) {}
  };

  extern constexpr A a(1, 2.0, 3);

  extern constexpr A b(4, 5, "hello");

  struct B {
    int n;
  };

  B c;
  B c2 = B();

  B d[10];

  struct C {
    constexpr C() : c(0) {}
    int c;
  };

  C e[10];

  struct D {
    constexpr D() : d(5) {}
    int d;
  };

  D f;

  union E {
    int a;
    void *b = &f;
  };

  E g;

  E h = E();
}

namespace BaseClass {
  template<typename T, unsigned> struct X : T {};
  struct C { char c = 1; };
  template<unsigned... Ns> struct Cs : X<C,Ns>... {};
  struct N { int n = 3; };
  struct D { double d = 4.0; };

  template<typename ...Ts>
  struct Test : Ts... { constexpr Test() : Ts()..., n(5) {} int n; };

  using Test1 = Test<N, C, Cs<1,2>, D, X<C,1>>;
  extern constexpr Test1 t1 = Test1();

  struct DN : D, N {};
  struct DND : DN, X<D,0> {};
  struct DNN : DN, X<N,0> {};
  extern constexpr DND dnd = DND();
  extern constexpr DNN dnn = DNN();

  struct E {};
  struct Test2 : X<E,0>, X<E,1>, X<E,2>, X<E,3> {};
  extern constexpr Test2 t2 = Test2();

  struct __attribute((packed)) PackedD { double y = 2; };
  struct Test3 : C, PackedD { constexpr Test3() {} };
  extern constexpr Test3 t3 = Test3();
}

namespace Array {
  extern constexpr int arr[2] = { 4 };

  extern constexpr char c[6][4] = { "foo", "a", { "bar" }, { 'x', 'y', 'z' }, { "b" }, '1', '2', '3' };

  extern constexpr unsigned char uc[] = { "foo" };

  struct C { constexpr C() : n(5) {} int n, m = 3 * n + 1; };
  extern const C ctors[3];
  constexpr C ctors[3];

  struct D { int n[2]; int m[3]; } extern constexpr d = { 1, 2, 3, 4, 5 };

  struct E {
    char c[4];
    char d[4];
    constexpr E() : c("foo"), d("x") {}
  };
  extern constexpr E e = E();

  struct F { constexpr F() : n(4) {} int n; };
  F f1[1][1][0] = { };
  F f2[2][2][2] = { };
}

namespace MemberPtr {
  struct B1 {
    int a, b;
    virtual void f();
    void g();
  };
  struct B2 {
    int c, d;
    virtual void h();
    void i();
  };
  struct C : B1 {
    int e;
    virtual void j();
    void k();
  };
  struct D : C, B2 {
    int z;
    virtual void l();
    void m();
  };

  extern constexpr int (D::*da) = &B1::a;
  extern constexpr int (D::*db) = &C::b;
  extern constexpr int (D::*dc) = &B2::c;
  extern constexpr int (D::*dd) = &D::d;
  extern constexpr int (D::*de) = &C::e;
  extern constexpr int (D::*dz) = &D::z;

  extern constexpr int (B1::*ba) = (int(B1::*))&B1::a;
  extern constexpr int (B1::*bb) = (int(B1::*))&C::b;
  extern constexpr int (B2::*bc) = (int(B2::*))&B2::c;
  extern constexpr int (B2::*bd) = (int(B2::*))&D::d;
  extern constexpr int (B1::*be) = (int(B1::*))&C::e;
  extern constexpr int (B1::*b1z) = (int(B1::*))&D::z;
  extern constexpr int (B2::*b2z) = (int(B2::*))&D::z;

  extern constexpr void (D::*df)() = &C::f;
  extern constexpr void (D::*dg)() = &B1::g;
  extern constexpr void (D::*dh)() = &B2::h;
  extern constexpr void (D::*di)() = &D::i;
  extern constexpr void (D::*dj)() = &C::j;
  extern constexpr void (D::*dk)() = &C::k;
  extern constexpr void (D::*dl)() = &D::l;
  extern constexpr void (D::*dm)() = &D::m;

  extern constexpr void (B1::*bf)()  = (void(B1::*)())&C::f;
  extern constexpr void (B1::*bg)()  = (void(B1::*)())&B1::g;
  extern constexpr void (B2::*bh)()  = (void(B2::*)())&B2::h;
  extern constexpr void (B2::*bi)()  = (void(B2::*)())&D::i;
  extern constexpr void (B1::*bj)()  = (void(B1::*)())&C::j;
  extern constexpr void (B1::*bk)()  = (void(B1::*)())&C::k;
  extern constexpr void (B1::*b1l)() = (void(B1::*)())&D::l;
  extern constexpr void (B1::*b1m)() = (void(B1::*)())&D::m;
  extern constexpr void (B2::*b2l)() = (void(B2::*)())&D::l;
  extern constexpr void (B2::*b2m)() = (void(B2::*)())&D::m;
}

namespace LiteralReference {
  struct Lit {
    constexpr Lit() : n(5) {}
    int n;
  };

  const Lit &lit = Lit();

  const Lit &lit2 = {};

  struct A { int &&r1; const int &&r2; };
  struct B { A &&a1; const A &&a2; };
  B b = { { 0, 1 }, { 2, 3 } };

  struct Subobj {
    int a, b, c;
  };
  constexpr int &&so = Subobj{ 1, 2, 3 }.b;

  struct Dummy { int padding; };
  struct Derived : Dummy, Subobj {
    constexpr Derived() : Dummy{200}, Subobj{4, 5, 6} {}
  };
  using ConstDerived = const Derived;
  constexpr const int &comma = (1, (2, ConstDerived{}).b);

  constexpr Subobj &&base = Derived{};

  constexpr Derived &derived = static_cast<Derived&>(base);
}

namespace NonLiteralConstexpr {
  constexpr int factorial(int n) {
    return n ? factorial(n-1) * n : 1;
  }
  extern void f(int *p);

  struct NonTrivialDtor {
    constexpr NonTrivialDtor() : n(factorial(5)), p(&n) {}
    ~NonTrivialDtor() {
      f(p);
    }

    int n;
    int *p;
  };
  static_assert(!__is_literal(NonTrivialDtor), "");
  NonTrivialDtor ntd;

  struct VolatileMember {
    constexpr VolatileMember() : n(5) {}
    volatile int n;
  };
  static_assert(!__is_literal(VolatileMember), "");
  VolatileMember vm;

  struct Both {
    constexpr Both() : n(10) {}
    ~Both();
    volatile int n;
  };
  Both b;

  void StaticVars() {
    static NonTrivialDtor ntd;
    static VolatileMember vm;
    static Both b;
  }
}

namespace VirtualMembers {
  struct A {
    constexpr A(double d) : d(d) {}
    virtual void f();
    double d;
  };
  struct B : A {
    constexpr B() : A(2.0), c{'h', 'e', 'l', 'l', 'o'} {}
    constexpr B(int n) : A(n), c{'w', 'o', 'r', 'l', 'd'} {}
    virtual void g();
    char c[5];
  };
  struct C {
    constexpr C() : n(64) {}
    int n;
  };
  struct D : C, A, B {
    constexpr D() : A(1.0), B(), s(5) {}
    short s;
  };
  struct E : D, B {
    constexpr E() : B(3), c{'b','y','e'} {}
    char c[3];
  };
  E e;

  struct nsMemoryImpl {
    virtual void f();
  };
  __attribute__((used))
  static nsMemoryImpl sGlobalMemory;

  template<class T>
  struct TemplateClass {
    constexpr TemplateClass() : t{42} {}
    virtual void templateMethod() {}

    T t;
  };
  TemplateClass<int> t;
}

namespace PR13273 {
  struct U {
    int t;
    U() = default;
  };

  struct S : U {
    S() = default;
  };

  extern const S s {};
}

namespace ArrayTemporary {
  struct A { const int (&x)[3]; };
  struct B { const A (&x)[2]; };
  B &&b = { { { { 1, 2, 3 } }, { { 4, 5, 6 } } } };
}

namespace UnemittedTemporaryDecl {
  constexpr int &&ref = 0;
  extern constexpr int &ref2 = ref;


}

namespace DR2126 {
  struct A { int &&b; };
  constexpr const A &a = {42};
  int &r = a.b;

  constexpr A &&b = {42};
  int &s = b.b;
}







namespace LocalVarInit {
  constexpr int f(int n) { return n; }
  struct Agg { int k; };
  struct Ctor { constexpr Ctor(int n) : k(n) {} int k; };
  struct Mutable { constexpr Mutable(int n) : k(n) {} mutable int k; };

  int scalar() { constexpr int a = { f(100) }; return a; }

  int agg() { constexpr Agg a = { f(101) }; return a.k; }

  int ctor() { constexpr Ctor a = { f(102) }; return a.k; }

  int mutable_() { constexpr Mutable a = { f(103) }; return a.k; }

#if __cplusplus >= 202002L
  struct Dtor { constexpr Dtor(int n) : k(n) {} constexpr ~Dtor() {} int k; };
  int dtor() { constexpr Dtor a = { f(103) }; return a.k; }
#endif
}

namespace CrossFuncLabelDiff {
  constexpr long a(bool x) { return x ? 0 : (long)&&lbl + (0 && ({lbl: 0;})); }
  void test() { static long b = (long)&&lbl - a(false); lbl: return; }
}

namespace VirtualBase {
  struct B {};
  struct D : virtual B {};
  D d;

  template<typename T> struct X : T {
    constexpr X() : T() {}
  };
  X<D> x;
}

namespace Unreferenced {
  int n;
  constexpr int *p = &n;
  int q = *p;


  constexpr int &r = n;
  int s = r;

  const int t = 1;
  const int &rt = t;
  int f(int);
  int u = f(rt);
}

namespace InitFromConst {
  template<typename T> void consume(T);

  const bool b = true;
  const int n = 5;
  constexpr double d = 4.3;

  struct S { int n = 7; S *p = 0; };
  constexpr S s = S();
  const S &r = s;
  constexpr const S *p = &r;
  constexpr int S::*mp = &S::n;
  constexpr int a[3] = { 1, 4, 9 };

  void test() {
    consume(b);

    consume(n);

    consume(d);

    consume<const S&>(s);

    consume<const S&>(r);

    consume(p);

    consume(mp);

    consume(a);
  }
}

namespace Null {
  decltype(nullptr) null();
  int *p = null();
  struct S {};
  int S::*q = null();
}

namespace InlineStaticConstRef {
  inline const int &fun() {
    static const int &i = 10;
    return i;
  }
  const int &use = fun();
}

namespace ClassTemplateWithStaticDataMember {
  template <typename T>
  struct S {
    static const int &a;
  };
  template <typename T>
  const int &S<T>::a = 5;
  const int &use = S<void>::a;
}

namespace ClassTemplateWithHiddenStaticDataMember {
  template <typename T>
  struct S {
    __attribute__((visibility("hidden"))) static const int &a;
  };
  template <typename T>
  const int &S<T>::a = 5;
  const int &use = S<void>::a;
}

namespace ClassWithStaticConstexprDataMember {
struct X {
  static constexpr const char &p = 'c';
};

const char *f() { return &X::p; }
}

struct PR69979 {
  const char (&d)[9];
} e {"12345678"};

