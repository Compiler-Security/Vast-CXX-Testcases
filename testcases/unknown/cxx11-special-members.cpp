// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

struct A {
  A(const A&);
  A &operator=(const A&);
};

struct B {
  A a;
  B(B&&) = default;
  B &operator=(B&&) = default;
};

void f1(B &x) {
  B b(static_cast<B&&>(x));
}

void f2(B &x, B &y) {
  x = static_cast<B&&>(y);
}


template<int> struct C { C() = default; };
struct D {
  C<0> c;
  D() { }
};
template struct C<0>; // was asserting
void f3() {
  C<0> a;
  D b;
}

