// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  virtual void f() = 0;
  A();
  ~A();
};

A::A() { }

A::~A() { }
