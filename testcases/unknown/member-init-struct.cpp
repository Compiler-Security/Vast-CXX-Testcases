// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {int a;};
struct B {float a;};
struct C {
  union {
    A a;
    B b[10];
  };
  _Complex float c;
  int d[10];
  void (C::*e)();
  C() : a(), c(), d(), e() {}
  C(A x) : a(x) {}
  C(void (C::*x)(), int y) : b(), c(y), e(x) {}
};
A x;
C a, b(x), c(0, 2);
