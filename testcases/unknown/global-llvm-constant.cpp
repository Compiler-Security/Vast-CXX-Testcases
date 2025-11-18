// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  A() { x = 10; }
  int x;
};

const A x;


struct X {
  int (*fp)(int, int);
};

int add(int x, int y) { return x + y; }

extern const X x2;
const X x2 = { &add };

struct X1 {
  mutable int i;
};

struct X2 {
  X1 array[3];
};

extern const X2 x2b;
const X2 x2b = { { { 1 }, { 2 }, { 3 } } };
