// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


void __attribute__ ((regparm (1)))  foo(int &a) {
}

struct S1 {
  int x;
  S1(const S1 &y);
};

void __attribute__((regparm(3))) foo2(S1 a, int b);
void bar2(S1 a, int b) {
  foo2(a, b);
}

struct S2 {
  int x;
};

void __attribute__((regparm(3))) foo3(struct S2 a, int b);
void bar3(struct S2 a, int b) {
  foo3(a, b);
}

struct S3 {
  struct {
    struct {} b[0];
  } a;
};
__attribute((regparm(2))) void foo4(S3 a, int b);
void bar3(S3 a, int b) {
  foo4(a, b);
}
