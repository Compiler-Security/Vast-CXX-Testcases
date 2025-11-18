// RUN: %driver -cc1 %isys %s -fdump-vtable-layouts %target -o %t%output-suffix && %filecheck


namespace Test1 {
  

struct A {
  virtual void f ();
  virtual void g ();
  virtual void h ();
  int ia;
};
void A::f() {}

struct B: public virtual A {
  void f ();
  void h ();
  int ib;
};
void B::f() {}

struct C: public virtual A {
  void g ();
  void h ();
  int ic;
};
void C::g() {}

struct D: public B, public C {
  void h ();
  int id;
};
void D::h() { }

struct X {
  int ix;
  virtual void x();
};

struct E : X, D {
  int ie;
  void f();
  void h ();
};
void E::f() { } 

}

namespace Test2 {


struct A { virtual void f(); };
struct B : virtual public A { int i; };
struct C : virtual public A { int j; };

struct D : public B, public C {
  virtual void d();
};
void D::d() { } 

}

namespace Test3 {


struct V1 {
  int v1;
  virtual void f();
};

struct V2 : virtual V1 {
  int v2;
  virtual void f();
};


struct C : virtual V1, virtual V2 {
  int c;
  virtual void f();
};
void C::f() { }

struct B {
  int b;
};



struct D : B, C {
  int d;
  virtual void g();
};
void D::g() { }

}
