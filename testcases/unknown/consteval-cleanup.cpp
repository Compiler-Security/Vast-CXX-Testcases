// RUN: %driver -cc1 %isys -std=c++20 -Wno-unused-value %s %target -o %t%output-suffix && %filecheck

struct P {
  consteval P() {}
};

struct A {
  A(int v) { this->data = new int(v); }
  ~A() { delete data; }
private:
  int *data;
};

void foo() {
  for (;A(1), P(), false;);
}
