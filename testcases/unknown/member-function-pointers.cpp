// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct A { int a; void f(); virtual void vf1(); virtual void vf2(); };
struct B { int b; virtual void g(); };
struct C : B, A { };

void (A::*pa)();
void (A::*volatile vpa)();
void (B::*pb)();
void (C::*pc)();

void (A::*pa2)() = &A::f;

void (A::*pa3)() = &A::vf1;

void (A::*pa4)() = &A::vf2;

void (C::*pc2)() = &C::f;

void (A::*pc3)() = &A::vf1;

void f() {
  pa = 0;

  vpa = 0;

  pc = pa;

  pa = static_cast<void (A::*)()>(pc);
}

void f2() {
  void (A::*pa2)() = &A::f;
  
  void (A::*pa3)() = &A::vf1;
  
  void (A::*pa4)() = &A::vf2;
}

void f3(A *a, A &ar) {
  (a->*pa)();
  (ar.*pa)();
}

bool f4() {
  return pa;
}

namespace PR5177 {
  struct A {
   bool foo(int*) const;
  } a;

  struct B1 {
   bool (A::*pmf)(int*) const;
   const A* pa;

   B1() : pmf(&A::foo), pa(&a) {}
   bool operator()() const { return (pa->*pmf)(new int); }
  };

  void bar(B1 b2) { while (b2()) ; }
}

namespace PR5138 {
  struct foo {
      virtual void bar(foo *);
  };

  extern "C" {
    void baz(foo *);
  }
  
  void (foo::*ptr1)(void *) = (void (foo::*)(void *))&foo::bar;
  void (*ptr2)(void *) = (void (*)(void *))&baz;

  void (foo::*ptr3)(void) = (void (foo::*)(void))&foo::bar;
}

namespace PR5593 {
  struct A { };
  
  bool f(void (A::*f)()) {
    return f && f;
  }
}

namespace PR5718 {
  struct A { };
  
  bool f(void (A::*f)(), void (A::*g)()) {
    return f == g;
  }
}

namespace BoolMemberPointer {
  struct A { };
  
  bool f(void (A::*f)()) {
    return !f;
  }

  bool g(void (A::*f)()) {
    if (!!f)
      return true;
    return false;
  }
}

namespace PR5940 {
  class foo {
  public:
    virtual void baz(void);
  };

  void foo::baz(void) {
       void (foo::*ptr)(void) = &foo::baz;
  }
}

namespace MemberPointerImpCast {
  struct A {
    int x;
  };
  struct B : public A {
  };
  void f(B* obj, void (A::*method)()) {
    (obj->*method)();
  }
}

namespace PR6258 {

  struct A {
    void f(bool);
  };

  void (A::*pf)(bool) = &A::f;

  void f() {
    void (A::*pf)(bool) = &A::f;
  }
}

namespace PR7027 {
  struct X { void test( ); };
  void testX() { &X::test; }
}

namespace test7 {
  struct A { void foo(); virtual void vfoo(); };
  struct B { void foo(); virtual void vfoo(); };
  struct C : A, B { void foo(); virtual void vfoo(); };

  void (C::*ptr0)() = &A::foo;
  void (C::*ptr1)() = &B::foo;
  void (C::*ptr2)() = &C::foo;
  void (C::*ptr3)() = &A::vfoo;
  void (C::*ptr4)() = &B::vfoo;
  void (C::*ptr5)() = &C::vfoo;
}

namespace test8 {
  struct X { };
  typedef int (X::*pmf)(int);
  
  pmf f() {
    return pmf();
  }
}

namespace test9 {
  struct A {
    void foo();
  };
  struct B : A {
    void foo();
  };

  typedef void (A::*fooptr)();

  struct S {
    fooptr p;
  };

  void test() {
    int x;
    static S array[] = { (fooptr) &B::foo };
  }
}

namespace test10 {
  struct A {
    int nonEmpty;
    void foo();
  };
  struct B : public A {
    virtual void requireNonZeroAdjustment();
  };
  struct C {
    int nonEmpty;
  };
  struct D : public C {
    virtual void requireNonZeroAdjustment();
  };



  void (A::*a)() = &A::foo;

  void (B::*b)() = (void (B::*)()) &A::foo;

  void (C::*c)() = (void (C::*)()) (void (B::*)()) &A::foo;

  void (D::*d)() = (void (C::*)()) (void (B::*)()) &A::foo;
}

namespace test11 {
  struct A { virtual void a(); };
  struct B : A {};
  struct C : B { virtual void a(); };
  void (C::*x)() = &C::a;

}
