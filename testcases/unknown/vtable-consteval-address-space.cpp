// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck


struct A {
  virtual consteval void DoNotEmit_f() {}
};
A a;

struct B {
  virtual void f() {}
  virtual consteval void DoNotEmit_g() {}
  virtual void h() {}
};
B b;

struct C {
  virtual ~C() = default;
  virtual consteval C &operator=(const C&) = default;
};
C c;

struct D : C {};
D d;

struct E { virtual void f() {} };
E e;

struct F : E { virtual consteval void DoNotEmit_g(); };
F f;
