// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

extern "C" {
int f();
int g();
}

struct A {
  A(int, int);
};


void foo() {
  A a{f(), g()};
}

struct B : A {
  B();
};
B::B() : A{f(), g()} {}
