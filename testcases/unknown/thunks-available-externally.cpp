// RUN: %driver -cc1 %isys %s -I%S %target -o %t%output-suffix && %filecheck

namespace Test1 {

struct Incomplete;

struct A {
  virtual void f();
  virtual void g(Incomplete);
  virtual void h();
  virtual void i();
  int a;
};

struct B {
  virtual void f();
  virtual void g(Incomplete);
  virtual void h();
  virtual void i();
  int b;
};

struct C : A, B {
  C();

  virtual void f();
  virtual void g(Incomplete);
  virtual void h();
  virtual void i();
};

void C::h() { }

C::C() { }

void C::i() { }

}

namespace Test2 {

struct A {
  virtual void f();
  int a;
};

struct B {
  virtual void f();
  int b;
};

struct C : A, B {
  virtual void f();
};

static void f(B* b) {
  b->f();
}

}

namespace Test3 {

struct A {
  virtual ~A();

  int a;
};

struct B : A { };
struct C : virtual B { };

void f() {
  C c;
}

}
