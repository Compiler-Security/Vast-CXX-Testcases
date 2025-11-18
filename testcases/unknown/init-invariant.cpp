// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck



struct A {
  A();
  int n;
};

extern const A a = A();

struct A2 {
  A2();
  constexpr ~A2() {}
  int n;
};

extern const A2 a2 = A2();


struct B {
  B();
  mutable int n;
};

extern const B b = B();

struct C {
  C();
  ~C();
  int n;
};

extern const C c = C();

int f();
extern const int d = f();

void e() {
  static const A a = A();
}






