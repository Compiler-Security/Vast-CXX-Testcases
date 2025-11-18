// RUN: %driver -cc1 %isys -Wno-error=non-pod-varargs %s %target -o %t%output-suffix && %filecheck

struct X {
  X();
  X(const X&);
  ~X();
};

void vararg(...);

void test(X x) {
  vararg(x);
}
