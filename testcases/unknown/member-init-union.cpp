// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

union x {
  int a;
  float b;
  x(float y) : b(y) {}
  x(int y) : a(y) {}
};
x a(1), b(1.0f);

