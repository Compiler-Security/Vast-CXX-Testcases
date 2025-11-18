// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  A& operator=(A&);
};

struct B {
  void operator=(B);
};

struct C {
  A a;
  B b;
  float c;
  int (A::*d)();
  _Complex float e;
  int f[10];
  A g[2];
  B h[2];
};
void a(C& x, C& y) {
  x = y;
}

