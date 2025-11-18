// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace PR43080 {
  int f(int i) { return sizeof i<i; }
}

namespace PR42861 {
  const unsigned long s = alignof(int);
  void foo() {  alignas(s) int j; }
}
