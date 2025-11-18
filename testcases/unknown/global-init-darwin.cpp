// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  A();
  ~A();
};

A a;
A as[2];

struct B {
  B();
  ~B();
  int f();
};

int i = B().f();

