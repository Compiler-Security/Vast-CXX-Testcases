// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct A {
  virtual int vf1() { return 1; }
  virtual int vf2() { return 2; }
};

int f(A* a, int (A::*fp)()) {
  return (a->*fp)();
}

int g1() {
  A a;
  return f(&a, &A::vf1);
}

int g2() {
  A a;
  return f(&a, &A::vf2);
}
