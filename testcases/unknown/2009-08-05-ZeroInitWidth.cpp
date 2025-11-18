// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct A {
  unsigned long long : (sizeof(unsigned long long) * 8) - 16;
};
struct B {
  A a;
};
struct B b = {
  {}
};
