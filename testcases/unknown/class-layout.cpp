// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace Test1 {
  struct A { } a;
}

namespace Test2 {
  struct A { void *a; int b; } a;
}

namespace Test3 {
  struct A { virtual void f(); int a; } a;
}

namespace Test4 {
  struct A {
    int a;
    char c;
    float b;
  };
  struct B : public A {
    short d;
    double e;
  } b;
}

namespace Test5 {
  struct A {
    virtual void f();
    char a;
  };

  struct B : A {
    char b : 1;
    char c;
  } b;
}

namespace Test6 {
  template <typename T> class A {
    T *foo;
  };

  class B;

  A<B> *a;

  class C {};
  class B : public C {
    A<B> a;
  };

  class E : public B {};
  E *e;
}

namespace Test7 {
  #pragma pack (1)
  class A {};
  class B {
     virtual ~B();
     A a;
  };
  B test(B b) { return b; }
  #pragma pack ()
}

namespace Test8 {
  struct A {};
  struct D { int a; };
  struct B : virtual D, A { };
  struct C : B, A { void f() {} };
  C c;
}
