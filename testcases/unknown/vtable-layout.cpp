// RUN: %driver -cc1 %isys %s -fdump-vtable-layouts %target -o %t%output-suffix && %filecheck

namespace test0 {
  struct Obj {};

  struct Base {           virtual const Obj *foo() = 0; };
  struct Derived : Base { virtual       Obj *foo() { return new Obj(); } };

  void test(Derived *D) { D->foo(); }
}

namespace Test1 {
struct A {
  virtual void f();
};
void A::f() { }

}

namespace Test2 {

struct A {
  virtual void f();
  virtual void f() const;
  
  virtual A* g(int a);
  virtual ~A();
  virtual void h();
  virtual A& operator=(const A&);
};
void A::f() { }


struct B {
  virtual void f();
  virtual void g() = 0;
  virtual ~B() = 0;
};
void B::f() { }

}

namespace Test3 {


struct A {
  virtual void f();
};
void A::f() { } 

struct B : A {
  virtual void f();
  virtual void g();
};
void B::f() { }

struct C : A {
  virtual void g();
  virtual void h();
};
void C::g() { }

struct D : B {
  virtual void f();
  virtual void g();
  virtual void h();
};

void D::f() { } 
}

namespace Test4 {


struct R1 { int r1; };
struct R2 { int r2; };
struct R3 : R1, R2 { int r3; };

struct A {
  virtual R2 *f();
};

struct B : A {
  virtual R3 *f();
};
R3 *B::f() { return 0; }

struct V1 { int v1; };
struct V2 : virtual V1 { int v1; };

struct C {
  virtual V1 *f(); 
};

struct D : C {
  virtual V2 *f();
};
V2 *D::f() { return 0; };

struct V3 : virtual R3 { int r3; };

struct E : A {
  virtual V3 *f();
};
V3 *E::f() { return 0;}


struct F : A {
  virtual void g();
  virtual R3 *f() = 0;
};
void F::g() { }

}

namespace Test5 {

struct A {
  virtual void f();
  virtual void g();
  int a;
};

struct B1 : A {
  virtual void f();
  int b1;
};

struct B2 : A {
  virtual void g();
  int b2;
};

struct C : B1, B2 {
  virtual void h();
};
void C::h() { }  
}

namespace Test6 {

struct A1 {
  virtual void f();
  int a;
};

struct A2 {
  virtual void f();
  int a;
};

struct C : A1, A2 {
  virtual void f();
};
void C::f() { }

}

namespace Test7 {


struct A {
  virtual void f();
  int a;
};

struct B1 : A { };
struct B2 : A { };

struct C { virtual void c(); };

struct D : C, B1, B2 {
  virtual void f();
};
void D::f() { }

}

namespace Test8 {


struct A { };

struct B : A {
  virtual void f();
};
void B::f() { }

}

namespace Test9 {


struct A1 { int a1; };
struct A2 { int a2; };

struct B : virtual A1, virtual A2 {
  int b;

  virtual void f();
};


void B::f() { }

}

namespace Test10 {

struct A1 { virtual void a1(); };
struct A2 { virtual void a2(); };

struct B : A1, A2 {
  int b;
};

struct C : B {
  virtual void f();
};
void C::f() { }

}

namespace Test11 {

struct A1 { int a; };
struct A2 { int b; };

struct B : A1, virtual A2 {
  int b;
};

struct C : virtual B {
  virtual void f();
};
void C::f() { }

}

namespace Test12 {


struct A1 {
  virtual void a1();
  int a;
};

struct A2 {
  virtual void a2();
  int a;
};

struct A3 {
  virtual void a3();
  int a;
};

struct A : A1, A2, A3 {
  virtual void a();
  int i;
};

struct B : virtual A {
  virtual void f();

  virtual void a();
};
void B::f() { } 

}

namespace Test13 {

struct A {
  virtual void f();
};

struct B : virtual A {
  virtual void f();
};

struct C : virtual B, virtual A {
  virtual void f();
};
void C::f() { }

}

namespace Test14 {


struct A { 
  virtual void f(); 
};

struct B : A { };

struct C : virtual B { };

struct D : C, virtual B {
 virtual void f();
};
void D::f() { }

}

namespace Test15 {

struct A { virtual void a(); };
struct B { virtual void b(); };

struct C : virtual B { };

struct D : A, virtual B, virtual C { 
  virtual void f();
};
void D::f() { } 

}

namespace Test16 {


struct A { virtual ~A(); };
struct B { virtual ~B(); };

struct C : A, B { virtual ~C(); };

struct D : virtual C {
  virtual void f();
};
void D::f() { } 

}

namespace Test17 {

struct A { virtual void f(); };
struct B : virtual A { virtual void f(); };
struct C : virtual A { virtual void f(); };
struct D : virtual B, virtual C { virtual void f(); };

class E : virtual D {
  virtual void f();  
};
void E::f() {}

}

namespace Test18 {


struct A {
  virtual void f();
  virtual void g();
};

struct B : virtual A {
  virtual void f();
};

struct C : A, B {
  virtual void g();
};




struct D : virtual B, virtual C, virtual A 
{
  virtual void f();
  virtual void h();
};
void D::f() {}

}

namespace Test19 {


struct A {
  int a;

  virtual void f();
};

struct B : A {
  int b;

  virtual void g();
};

struct C {
  virtual void c();
};

struct D : C, B, virtual A {
  virtual void f();
};
void D::f() { }

}

namespace Test20 {


struct A {
  virtual void f() = 0;
  virtual void g();
};

struct B : A { };

struct C : A, B {
  virtual void f() = 0;
  virtual void h();
};
void C::h() { }

}

namespace Test21 {

struct A { 
  virtual void f();
};

struct B : virtual A { };
class C : virtual B { };
class D : virtual C { };

class E : virtual C { };

class F : virtual D, virtual E {
  virtual void f();
};
void F::f() { }

}

namespace Test22 {

struct V1 {
  int v1;
}; 

struct V2 : virtual V1 {
  int v2; 
};



struct C : virtual V1, virtual V2 {
  int c; 
  virtual void f(); 
};
void C::f() { } 

}

namespace Test23 {

struct A {
  int a;
};

struct B : virtual A {
  int b;
};

struct C : A, virtual B {
  int c;
};




struct D : virtual A, virtual B, C {
  int d;

  void f();
};
void D::f() { } 
  D d;
}

namespace Test24 {


struct A {
  virtual void f();
};

struct B : virtual A { };
struct C : virtual A { };



struct D : B, C {
  virtual void f();
};
void D::f() { }

}

namespace Test25 {
  

struct V {
  virtual void f();
};

struct A : virtual V { };
struct B : virtual V { };



struct C : A, virtual V, B {
  virtual void g();
};
void C::g() { }

}

namespace Test26 {


struct A {
  virtual void a();
};

struct B {
  virtual void c();
};

struct C : virtual A {
  virtual void b();
};


class D : virtual B, virtual C {
  virtual void d();
};
void D::d() { } 

}

namespace Test27 {


struct A {
  virtual void a();
};

struct B {
  virtual void b();
};

struct C {
  virtual void c();
};

struct D : A, virtual B, C {
  virtual void d();
};


struct E : D {
  virtual void e();
};
void E::e() { }

}

namespace Test28 {


struct A {
  virtual void a();
};

struct B {
  virtual void b();
};

struct C : A, B {
  virtual void c();
};

struct D : virtual C {
};


struct E : D {
  virtual void e();
};
void E::e() { }

}

namespace Test29 {


struct V1 { };
struct V2 : virtual V1 { };

struct A {
  virtual V1 *f();
};

struct B : virtual A {
  virtual V2 *f();
};
V2 *B::f() { return 0; }

}

namespace Test30 {

struct A { };

struct B : virtual A {
 int i;
};

struct C {
 virtual void f();
};

struct D : virtual C, B { };
struct E : virtual D { };

struct F : E {
 virtual void f();
};
void F::f() { }

}

namespace Test31 {

struct A {
  int a;
};

struct B {
  virtual void f();
};

struct C : A, virtual B {
  virtual void f();
};

struct D : virtual C {
  virtual void f();
};
void D::f() { }

}

namespace Test32 {


struct A {
  virtual void f();
};

struct B : virtual A { };
struct C : A, virtual B { };
struct D : virtual B { };

struct E : C, virtual D {
  virtual void f();
};
void E::f() { }

}

namespace Test33 {


struct A {
  virtual void a();
};

struct B {
  virtual void b();
};

struct C : virtual A, virtual B {
  virtual void c();
};

struct D : virtual C { };

struct E : A, D { 
  virtual void e();
};

struct F : virtual E, A {
  virtual void f();
};
void F::f() { }

}

namespace Test34 {


struct A {
  virtual void a();
};
struct B : virtual A { };

struct C : B, A {
  virtual void c();
};

struct D : A, C { };

struct E : virtual D {
  virtual void e();
};

struct F : E {
  virtual void f();
};
void F::f() { }

}

namespace Test35 {


struct A {
 virtual void a();

 int i;
};

struct B : virtual A {
 virtual void b();
};

struct C {
 virtual void c();
};

struct D : C, virtual B {
 virtual void d();
};

struct E : D {
 virtual void e();

 bool b;
};

struct F : virtual D { };
struct G : virtual E { };

struct H : F, G {
 virtual void h();
};
void H::h() { }

}

namespace Test36 {


struct A {
 virtual void f();
};

struct B : virtual A { };

struct C : virtual A {
 virtual void f();
};

struct D : virtual B, C {
 virtual void g();
};
void D::g() { }

}

namespace Test37 {

struct A {
	virtual A* f() = 0; 
};

struct B : virtual A {
  virtual B* f();
};

struct C : B {
  virtual C* f();
};

C* C::f() { return 0; }

}

namespace Test38 {
  struct A {
    virtual void *foo();
    virtual const void *foo() const;
  };

  class B : virtual public A {
    void *foo();
    const void *foo() const;
  };

  void *B::foo() { return 0; }
}

namespace Test39 {
  struct A {
    virtual void foo() = delete;
  };

  struct B: A {
    virtual void foo2();
  };

  void B::foo2() {
  }
}

namespace Test40 {
  struct A {
    virtual void foo() = 0;
  };

  struct B : public A {
    virtual void foo();
  };

  struct C: public B {
    virtual int f(int);
    virtual int f();
    virtual int g(int);
    virtual int g();
    virtual int h(int);
    virtual int h();
    virtual int i(int);
    virtual int i();
  };
  int C::f() { return 1; }

  class D : C {};

  D d;
}
