// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck


int make_a();

static union {
  int a = make_a();
  char *b;
};

int f() { return a; }



int g() {
  union {
    int a;
    int b = 81;
  };
  return b;
}

struct A {
  A();
};
union B {
  int k;
  struct {
    A x;
    int y = 123;
  };
  B() {}
  B(int n) : k(n) {}
};

B b1;
B b2(0);




