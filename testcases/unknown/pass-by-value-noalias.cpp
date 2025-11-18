// RUN: %driver -cc1 %isys -fpass-by-value-is-noalias -disable-llvm-optzns %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -disable-llvm-optzns %s %target -o %t%output-suffix && %filecheck

struct Foo {
  int a;
  int b;
  int c;
  int d;
  int e;
  int f;
};


void take(Foo arg) {}

int G;

struct NonTrivial {
  int a;
  int b;
  int c;
  int d;
  int e;
  int f;

  NonTrivial(const NonTrivial &Other) {
    a = G + 10 + Other.a;
  }
};


void take(NonTrivial arg) {}

struct A {
  A(A **where) : data{"hello world 1"} {
    *where = this; //Escaped pointer 1 (proposed UB?)
  }

  A() : data{"hello world 2"} {}

  char data[32];
};
A *p;

void take(A arg) {}

A CreateA(A **where) {
  A justlikethis;
  *where = &justlikethis; //Escaped pointer 2 (should also be UB, then)
  return justlikethis;
}

void test() {
  take({&p});        // 1
  take(CreateA(&p)); // 2
}
