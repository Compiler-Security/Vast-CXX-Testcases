// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

namespace Test1 {
struct A { };

struct B : virtual A {
  virtual void f();
};

void B::f() { }
}

namespace Test2 {
  struct A { };

  struct B : A { virtual void f(); };
  struct C : virtual B { };

  C c;
}

namespace Test3 {
  class A1 { int i; };
  class A2 { int i; virtual void f(); };
  class V1 : public A1, public A2 { int i; };
  class B1 { int i; };
  class B2 { int i; };
  class V2 : public B1, public B2, public virtual V1 { int i; };
  class V3 {virtual void g(); };
  class C1 : public virtual V1 { int i; };
  class C2 : public virtual V3, virtual V2 { int i; };
  class X1 { int i; };
  class C3 : public X1 { int i; };
  class D : public C1, public C2, public C3 { int i;  };

  D d;
}

namespace Test4 {
  class A1 { int i; };
  class A2 { int i; virtual void f(); };
  class V1 : public A1, public virtual A2 { int i; };
  class B1 { int i; };
  class B2 { int i; };
  class V2 : public B1, public B2, public virtual V1 { int i; };
  class V3 {virtual void g(); };
  class C1 : public virtual V1 { int i; };
  class C2 : public virtual V3, virtual V2 { int i; };
  class X1 { int i; };
  class C3 : public X1 { int i; };
  class D : public C1, public C2, public C3 { int i;  };

  D d;
}

namespace Test5 {
  struct A {
    virtual void f() = 0;
    virtual void anchor();
  };

  void A::anchor() {
  }
}

namespace Test6 {
  struct A {
    virtual void f() = delete;
    virtual void anchor();
  };

  void A::anchor() {
  }
}

