// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
# 99 "someheader.h"
class A {
public:
  A();
  int foo() { return 0; }
};
# 5 "main.cpp"
A a;

int f() {
  return a.foo();
}

