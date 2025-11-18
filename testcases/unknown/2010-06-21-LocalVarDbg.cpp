// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

class A {
public:
  ~A() { int i = 0; i++; }
};

int foo(int i) {
  A a;
  return 0;
}
