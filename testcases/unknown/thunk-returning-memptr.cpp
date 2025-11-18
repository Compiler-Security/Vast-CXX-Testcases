// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct X;
typedef void (X::*memptr)();

struct A {
  virtual memptr f();
};

struct B {
  virtual memptr f();
};

struct C : A, B {
  C();
  memptr f() override __attribute__((noinline)) { return nullptr; };
};

C::C() {}


