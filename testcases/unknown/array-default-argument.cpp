// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++98 -fexceptions -fcxx-exceptions %target -o %t%output-suffix && %filecheck

struct A {
  A();
  ~A();
};

struct B {
  B(A = A());
  ~B();
};

void f();
void g() {

  B b[5];

  f();

}
