// RUN: %driver -cc1 %isys %s -fstrict-vtable-pointers %target -o %t%output-suffix && %filecheck

struct A {
  virtual void foo();
};

struct D : A {
  void foo();
};

void testExternallyVisible() {
  A *a = new A;

  a->foo();

  D *d = new D;
  d->foo();
  A *a2 = d;
  a2->foo();
}

namespace {

struct B {
  virtual void bar();
};

struct C : B {
  void bar();
};

}

void testInternallyVisible(bool p) {
  B *b = new B;
  b->bar();

  C *c = new C;
  c->bar();
}





