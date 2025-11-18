// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct S;
extern S a[10];
S(*b)[10] = &a;
struct S {
  int x;
};


int f() { return a[3].x; }
