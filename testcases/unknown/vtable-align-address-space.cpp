// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

struct A {
  virtual void f();
  virtual void g();
  virtual void h();
};

void A::f() {}

