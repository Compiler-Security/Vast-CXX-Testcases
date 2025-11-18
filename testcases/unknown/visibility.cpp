// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fvisibility=hidden %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fvisibility=internal %target -o %t%output-suffix && %filecheck

#define HIDDEN __attribute__((visibility("hidden")))
#define PROTECTED __attribute__((visibility("protected")))
#define DEFAULT __attribute__((visibility("default")))

namespace test30 {
  struct H {
  };
  template<H *T>
  struct X {
  };
  H DEFAULT a;
  X<&a> b;
}

namespace test25 {
  template<typename T>
  struct X {
    template<typename U>
    struct definition {
    };
  };

  class DEFAULT A { };

  X<int>::definition<A> a;
}

namespace test28 {
  class DEFAULT foo {
  };
  foo myvec;
}

namespace test29 {
#pragma GCC visibility push(hidden)
  struct RECT {
    int top;
  };
  DEFAULT extern RECT data_rect;
  RECT data_rect = { -1};
#pragma GCC visibility pop
}

namespace test40 {
  template<typename T>
  struct foo {
    DEFAULT static int bar;
  };
  template<typename T>
  int foo<T>::bar;
  template struct foo<int>;
}

namespace test41 {
  struct HIDDEN foo {};
  extern foo bar;
  foo *zed() {
    return &bar;
  }
}

namespace test48 {
  struct HIDDEN foo {
  };
  DEFAULT foo x;

  struct bar {
    template<foo *z>
    struct zed {
    };
  };

  bar::zed<&x> y;
}

namespace test72 {
  template <class T>
  struct foo {
    HIDDEN static int var1;
    template <class U> HIDDEN static U var2;
  };
  template <class T> template <class U>
  U foo<T>::var2;

  extern template struct DEFAULT foo<int>;

  int use() {
    foo<int> o;
    foo<long> p;
    return o.var1 + o.var2<int> + p.var1 + p.var2<int>;
  }
}

namespace test73 {
  struct HIDDEN foo {};
  DEFAULT foo da, db, dc, dd;
  HIDDEN foo ha, hb, hc, hd;
  template<foo *z> DEFAULT int var;

  template int var<&da>;
  template int DEFAULT var<&db>;
  template int HIDDEN var<&dc>;
  template int var<&ha>;
  template int DEFAULT var<&hb>;
  template int HIDDEN var<&hc>;

  int use() { return var<&dd> + var<&hd>; }

}


namespace test27 {
  template<typename T>
  class C {
    class DEFAULT D {
      void f();
    };
  };

  template<>
  class C<int>::D {
    virtual void g();
  };

  void C<int>::D::g() {
  }
}








namespace Test1 {
  void HIDDEN f() { }
  
}

namespace Test2 {
  struct HIDDEN A {
    void f();
  };

  void A::f() { }
}
 
namespace Test3 {
  struct HIDDEN A {
    struct B {
      void f();
    };
  };

  void A::B::f() { }  
}

namespace Test4 HIDDEN {
  int VariableInHiddenNamespace = 10;

  void g() { } 
  
  struct DEFAULT A {
    void f();
  };
  
  void A::f() { } 
}

namespace Test5 {

  namespace NS HIDDEN {
    void f() { }
  }
  
  namespace NS {
    void g() { }
  }
}

namespace Test6 {
  struct HIDDEN foo {
    foo() { }
    void bonk();
    virtual void bar() = 0;

    virtual void zonk() {}
  };

  struct barc : public foo {
    barc();
    virtual void bar();
  };

  barc::barc() {}
}

namespace Test7 {
  class HIDDEN A {};
  A a; // top of file

  template <A&> struct Aref {
    static void foo() {}
  };

  class B : public A {};
  B b; // top of file

  void test() {
    Aref<a>::foo();
  }
}

namespace Test8 {
  void foo();
  void bar() {}

  void test() {
    foo();
    bar();
  }
}

namespace Test9 {
  extern "C" {
    struct A { int field; };
    void DEFAULT test9_fun(struct A *a) { }
    struct A DEFAULT test9_var; // above
  }

  void test() {
    A a = test9_var;
    test9_fun(&a);
  }
}

namespace Test10 {
  struct A;

  class DEFAULT B {
    void foo(A*);
  };

  void B::foo(A*) {}
}

namespace Test11 {
  struct A {
    void foo() {}
    void DEFAULT bar() {}
  };

  void test() {
    A a;
    a.foo();
    a.bar();
  }

}

namespace Test12 {
  struct A {
    static int hidden HIDDEN;

    static int visible;
  };

  void test() {
    A::hidden = 0;
    A::visible = 0;
  }
}

namespace Test13 {
  struct HIDDEN A {};

  struct B {
    static A a;
  };
  A B::a;

  struct DEFAULT C {
    static A a;
  };
  A C::a;
};

namespace Test14 {
  extern struct A *var;

  struct A *test() { return var; }
}

namespace Test15 {
  struct A {};
  template <class T> struct Temp {
    struct Inner {
      static char buffer[0];
    };
  };

  char *test() {
    return Temp<A>::Inner::buffer;
  }
}

namespace Test16 {
  struct Base1 { virtual void foo(); };
  struct Base2 : virtual Base1 { virtual void foo(); };
  template <class T> struct A : virtual Base1, Base2 {
    virtual void foo();
  };
  extern template struct A<char>;

  void test() {
    A<char> a;
    a.foo();
  }
}

namespace Test17 {
  struct HIDDEN A {
    static void foo();
    static void DEFAULT bar();
    static void HIDDEN baz();

    struct DEFAULT B {
      static void foo();
      static void DEFAULT bar();
      static void HIDDEN baz();
    };
  };

  void test() {
    A::foo();
    A::bar();
    A::baz();
    A::B::foo();
    A::B::bar();
    A::B::baz();
  }
}

namespace Test18 {
  template <class T> struct HIDDEN A {
    static void foo();
    static void DEFAULT bar();
    static void HIDDEN baz();

    struct DEFAULT B {
      static void foo();
      static void DEFAULT bar();
      static void HIDDEN baz();
    };
  };
  struct HIDDEN H;

  void test() {
    A<int>::foo();
    A<int>::bar();
    A<int>::baz();
    A<int>::B::foo();
    A<int>::B::bar();
    A<int>::B::baz();
    A<H>::foo();
    A<H>::bar();
    A<H>::baz();
    A<H>::B::foo();
    A<H>::B::bar();
    A<H>::B::baz();
  }
}

namespace Test19 {
  struct A { A(); ~A(); };

  template <class T> void foo() {
    static A a;
  }

  void test() {
    foo<int>();
  }
}

namespace Test20 {
  template <unsigned> struct HIDDEN A {};

  template <> struct A<0> {
    static void test0();
    static void test1();
  };

  void A<0>::test0() {}

  void test1() {
    A<0>::test1();
  }

  template <> struct DEFAULT A<1> {
    static void test2();
    static void test3();
  };

  void A<1>::test2() {}

  void test3() {
    A<1>::test3();
  }

  template <class T> struct B {
    static void test4() {}
    static void test5();
  };

  void test4() {
    B<A<2> >::test4();
  }

  void test5() {
    B<A<2> >::test5();
  }
}

namespace test21 {
  enum En { en };
  template<En> struct A {
    DEFAULT void foo() {}
  };

  template void A<en>::foo();
}

namespace test22 {
  class A1 {};
  class A2 {};

  template <class T> struct B {};
  template <> struct DEFAULT B<A1> {
    static void foo();
    static void bar() {}
  };
  template <> struct B<A2> {
    static void foo();
    static void bar() {}
  };

  void test() {
    B<A1>::foo();
    B<A1>::bar();
    B<A2>::foo();
    B<A2>::bar();
  }
}

namespace PR10113 {
  namespace foo DEFAULT {
    template<typename T>
      class bar {
      void zed() {}
    };
  }
  template class foo::bar<char>;

  struct zed {
  };
  template class foo::bar<zed>;
}

namespace PR11690 {
  template<class T> struct Class {
    void size() const {
    }
  };
  template class DEFAULT Class<char>;

  template<class T> void Method() {}
  template  DEFAULT void Method<char>();
}

namespace PR11690_2 {
  namespace foo DEFAULT {
    class bar;
    template<typename T1, typename T2 = bar>
    class zed {
      void bar() {
      }
    };
  }
  struct baz {
  };
  template class foo::zed<baz>;
}

namespace test23 {
  template <typename T>
  struct X {
    static void f() {
    }
  };

  class DEFAULT A;

  void g() {
    X<A> y;
    y.f();
  }
}

namespace PR12001 {
  template <typename P1>
  void Bind(const P1& p1) {
  }

  class DEFAULT Version { };

  void f() {
    Bind(Version());
  }
}

namespace test24 {
  class DEFAULT A { };

  struct S {
    template <typename T>
    void mem() {}
  };

  void test() {
    S s;
    s.mem<A>();
  }
}

namespace test26 {
  template<typename T>
  class C {
    DEFAULT  void f();
  };

  template<>
  void C<int>::f() { }

}

namespace test31 {
  struct A {
    struct HIDDEN B {
      static void DEFAULT baz();
    };
  };
  void f() {
    A::B::baz();
  }
}

namespace test32 {
  struct HIDDEN A {
    struct DEFAULT B {
      void DEFAULT baz();
    };
  };
  void A::B::baz() {
  }
}

namespace test33 {
  template<typename T>
  class foo {
    void bar() {}
  };
  struct HIDDEN zed {
  };
  template class DEFAULT foo<zed>;
}

namespace test34 {
  struct foo {
  };
  template<class T>
  void bar() {}
  template DEFAULT void bar<foo>();
}

namespace test35 {
  template<typename T>
  struct DEFAULT foo {
    void bar() {}
  };
  class zed;
  template class foo<zed>;
  class DEFAULT zed {
  };
}

namespace test36 {
  template<typename T1, typename T2>
  class foo {
    void bar() {}
  };
  class DEFAULT S1 {};
  struct HIDDEN S2 {};
  template class foo<S1, S2>;
}

namespace test37 {
  struct HIDDEN foo {
  };
  template<class T>
  DEFAULT void bar() {}
  template DEFAULT void bar<foo>();
}

namespace test38 {
  template<typename T>
  class DEFAULT foo {
    void bar() {}
  };
  struct HIDDEN zed {
  };
  template class foo<zed>;
}

namespace test39 {
  class DEFAULT default_t;
  class HIDDEN hidden_t;
  template <class T> class A {
    template <class U> class B {
      HIDDEN void hidden() {}
      void noattr() {}
      template <class V> void temp() {}
    };
  };
  template class DEFAULT A<hidden_t>;
  template class DEFAULT A<hidden_t>::B<hidden_t>;
  template void A<hidden_t>::B<hidden_t>::temp<default_t>();
  template void A<hidden_t>::B<hidden_t>::temp<hidden_t>();




}

namespace test42 {
  struct HIDDEN foo {
  };
  template <class P>
  struct bar {
  };
  template <>
  struct HIDDEN bar<foo> {
    DEFAULT static void zed();
  };
  void bar<foo>::zed() {
  }
}

namespace test43 {
  struct HIDDEN foo {
  };
  template <class P>
  void bar() {
  }
  template <>
  DEFAULT void bar<foo>() {
  }
}

namespace test44 {
  template <typename T>
  struct foo {
    foo() {}
  };
  namespace {
    struct bar;
  }
  template struct DEFAULT foo<bar>;
  foo<bar> x;
}

namespace test45 {
  template <typename T>
  struct foo {
    template <typename T2>
    struct bar {
      bar() {};
    };
  };
  namespace {
    struct zed;
  }
  template struct DEFAULT foo<int>::bar<zed>;
  foo<int>::bar<zed> x;
}

namespace test46 {
  template <typename T>
  void foo() {
  }
  namespace {
    struct bar;
  }
  template DEFAULT void foo<bar>();
  void zed() {
    foo<bar>();
  }
}

namespace test47 {
  struct foo {
    template <typename T>
    static void bar() {
    }
  };
  namespace {
    struct zed;
  }
  template DEFAULT void foo::bar<zed>();
  void baz() {
    foo::bar<zed>();
  }
}

namespace test49 {

  struct HIDDEN foo {
  };

  DEFAULT foo x;

  struct bar {
    template<foo *z>
    void zed() {
    }
  };

  template void bar::zed<&x>();
}

namespace test50 {

  struct HIDDEN foo {
  };
  DEFAULT foo x;
  template<foo *z>
  struct DEFAULT bar {
    void zed() {
    }
  };
  template void bar<&x>::zed();
}

namespace test51 {

  struct HIDDEN foo {};
  DEFAULT foo da, db, dc, dd, de, df;
  HIDDEN foo ha, hb, hc, hd, he, hf;
  template<foo *z>
  void DEFAULT zed() {
  }
  template void zed<&da>();

  template void DEFAULT zed<&db>();

  template void HIDDEN zed<&dc>();

  template void zed<&ha>();

  template void DEFAULT zed<&hb>();

  template void HIDDEN zed<&hc>();

#pragma GCC visibility push(hidden)
  template void zed<&dd>();
  template void zed<&hd>();
  template void DEFAULT zed<&he>();
#pragma GCC visibility pop

  void use() {
    zed<&df>();
    zed<&hf>();
  }
}

namespace test52 {

  namespace {
    struct foo {
    };
  }
  template<foo *x>
  void zed() {
  }
  void f() {
    zed<nullptr>();
  }
}

namespace test53 {
  template<typename _Tp > struct vector   {
    static void       _M_fill_insert();
  };
#pragma GCC visibility push(hidden)
  enum zed {v1};

  template<>
  struct vector<int> {
    static void       _M_fill_insert();
  };
  void foo() {
    vector<unsigned>::_M_fill_insert();
    vector<int>::_M_fill_insert();
    vector<zed>::_M_fill_insert();
  }
#pragma GCC visibility pop
}

namespace test54 {
  template <class T>
  struct foo {
    static void bar();
  };
#pragma GCC visibility push(hidden)
  class zed {
    zed(const zed &);
  };
  void bah() {
    foo<zed>::bar();
  }
#pragma GCC visibility pop
}

namespace test55 {
  template <class T>
  struct HIDDEN foo {
    static void bar();
  };
  template <class T> struct foo;
  void foobar() {
    foo<int>::bar();
  }
}

namespace test56 {
  template <class T> struct foo;
  template <class T>
  struct HIDDEN foo {
    static void bar();
  };
  void foobar() {
    foo<int>::bar();
  }
}

namespace test57 {
#pragma GCC visibility push(hidden)
  template <class T>
  struct foo;
  void bar(foo<int>*);
  template <class T>
  struct foo {
    static void zed();
  };
  void bah() {
    foo<int>::zed();
  }
#pragma GCC visibility pop
}

namespace test58 {
#pragma GCC visibility push(hidden)
  struct foo;
  template<typename T>
  struct DEFAULT bar {
    static void zed() {
    }
  };
  void bah() {
    bar<foo>::zed();
  }
#pragma GCC visibility pop
}

namespace test59 {
  DEFAULT int f();
  HIDDEN int g();
  typedef int (*foo)();
  template<foo x, foo y>
  void test() {}
  void use() {
    test<&g, &f>();

    test<&f, &g>();
  }
}

namespace test60 {
  template<int i>
  class HIDDEN a {};
  template<int i>
  class DEFAULT b {};
  template<template<int> class x, template<int> class y>
  void test() {}
  void use() {
    test<a, b>();

    test<b, a>();
  }
}

namespace test61 {
  template <typename T1>
  struct Class1
  {
    void f1() { f2(); }
    inline void f2();
  };
  template<>
  inline void Class1<int>::f2()
  {
  }
  void g(Class1<int> *x) {
    x->f1();
  }
}
namespace test61 {
  template class HIDDEN Class1<int>;
}

namespace test62 {
  template <typename T1>
  struct Class1
  {
    void f1() { f2(); }
    inline void f2() {}
  };
  template<>
  inline void Class1<int>::f2()
  {
  }
  void g(Class1<int> *x) {
    x->f2();
  }
}
namespace test62 {
  template class HIDDEN Class1<int>;
}

namespace test63 {
  enum HIDDEN E { E0 };
  struct A {
    template <E> static void foo() {}

    template <E> struct B {
      static void foo() {}
    };
  };

  void test() {
    A::foo<E0>();
    A::B<E0>::foo();
  }
}

namespace test64 {
  struct HIDDEN A {};
  template <class P> struct B {
    static DEFAULT void foo() {}
  };

  template class B<A>;
}

namespace test65 {
  class HIDDEN A {};
  template <class T> struct B {
    static void func();
    template <class U> static void funcT1();
    template <class U> static void funcT2();
    class Inner {};
    template <class U> class InnerT {};
  };
  template <template <class T> class Temp> struct C {
    static void foo() {}
  };

  template <> DEFAULT void B<A>::func() {}

  template <> template <> DEFAULT void B<A>::funcT2<A>() {}

  template <> template <class T> DEFAULT void B<A>::funcT1() {}

  template <> struct DEFAULT B<A>::Inner {
    static void foo() {}
  };

  template <> template <class U> struct DEFAULT B<A>::InnerT {
    static void foo() {}
  };

  void test() {
    B<A>::funcT1<int>();
    B<A>::funcT1<A>();
    B<A>::Inner::foo();
    B<A>::InnerT<int>::foo();
    B<A>::InnerT<A>::foo();
  }

  template class C<B<A>::InnerT>;
}

namespace test66 {
  template <typename T>
  struct DEFAULT barT {
    static void zed() {}
  };
  class foo;
  class DEFAULT foo;
  template struct barT<foo>;

  template <int* I>
  struct DEFAULT barI {
    static void zed() {}
  };
  extern int I;
  extern int I DEFAULT;
  template struct barI<&I>;

  typedef void (*fType)(void);
  template<fType F>
  struct DEFAULT barF {
    static void zed() {}
  };
  void F();
  void F() DEFAULT;
  template struct barF<F>;
}

namespace test67 {
  template <typename T>
  struct DEFAULT bar {
    static void zed() {}
  };

  class foo;
  class compute {
    void f(foo *rootfoo);
  };
  class DEFAULT foo;

  template struct bar<foo>;
}

namespace test68 {
  class A { public: ~A(); };
  class f {
  public:
    f() {
      static A test;
    }
  };
  void g() {
    f a;
  }
}

namespace test69 {
  namespace foo {
    void f();
  }
  namespace foo {
    void f() {};
  }
  namespace foo __attribute__((visibility("hidden"))) {
  }
}

namespace test70 {
  class HIDDEN A {
    virtual void a();
  };
  class HIDDEN B : virtual A {
    void a() override;
    ~B();
  };
  B::~B() {}

  class C {};
  class D : virtual C {};
  D d;
}

namespace test71 {
  template <class T>
  struct foo {
    static HIDDEN T zed();
    template <class U> HIDDEN U bar();
  };
  template <class T>
  T foo<T>::zed() { return {}; }
  template <class T> template <class U>
  U foo<T>::bar() { return {}; }

  extern template struct DEFAULT foo<int>;

  int use() {
    foo<int> o;
    foo<long> p;
    return o.zed() + o.bar<int>() + p.zed() + p.bar<int>();
  }
}
