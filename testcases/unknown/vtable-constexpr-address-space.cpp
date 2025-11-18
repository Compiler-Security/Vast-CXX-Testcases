// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck


struct DoNotEmit {
  virtual constexpr void f();
};
constexpr void DoNotEmit::f() {}

struct B {
  virtual constexpr void f() {}
};
B b;

struct CBase {
  virtual constexpr void f(); // not key function
};

struct C : CBase {
  void f(); // key function
};
void C::f() {}
