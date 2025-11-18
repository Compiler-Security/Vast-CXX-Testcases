// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct S {
  mutable int n;
};
int f() {
  static const S s = { 12 };
  return ++s.n;
}
