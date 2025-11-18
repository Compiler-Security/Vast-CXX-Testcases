// RUN: %driver -cc1 %isys -no-enable-noundef-analysis %s %target -o %t%output-suffix && %filecheck

void __attribute__((fastcall)) foo1(int &y);
void bar1(int &y) {
  foo1(y);
}

struct S1 {
  int x;
  S1(const S1 &y);
};

void __attribute__((fastcall)) foo2(S1 a, int b);
void bar2(S1 a, int b) {
  foo2(a, b);
}
