// RUN: %driver -cc1 %isys %s -Wno-unused-value -std=c++11 %target -o %t%output-suffix && %filecheck
namespace std {
struct type_info;
}

struct A {
  virtual ~A();
  operator bool();
};
struct B : A {};

void f1(A *x) { typeid(false, *x); }

void f2(bool b, A *x, A *y) { typeid(b ? *x : *y); }

void f3(bool b, A *x, A &y) { typeid(b ? *x : y); }

void f4(bool b, A &x, A *y) { typeid(b ? x : *y); }

void f5(volatile A *x) { typeid(*x); }

void f6(A *x) { typeid((B &)*(B *)x); }

void f7(A *x) { typeid((*x)); }

void f8(A *x) { typeid(x[0]); }

void f9(A *x) { typeid(0[x]); }

void f10(A *x, A *y) { typeid(*y ?: *x); }

void f11(A *x, A &y) { typeid(*x ?: y); }

void f12(A &x, A *y) { typeid(x ?: *y); }

void f13(A &x, A &y) { typeid(x ?: y); }

void f14(A *x) { typeid((const A &)(A)*x); }

void f15(A *x) { typeid((A &&)*(A *)nullptr); }
