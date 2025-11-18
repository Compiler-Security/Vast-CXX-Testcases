// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck





struct A {
  virtual void f();
  int a;
};
struct B : virtual A {
  virtual void g();
  int b;
};
B b;
