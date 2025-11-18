// RUN: %driver -cc1 %isys -fsymbol-partition=foo %s %target -o %t%output-suffix && %filecheck




struct S {
  virtual void f();
};

void S::f() {}

int gv;
extern "C" void *f() { return 0; }
void ifunc() __attribute__((ifunc("f")));
