// RUN: %driver -cc1 %isys -std=c++14 %s %target -o %t%output-suffix && %filecheck

template <class T> T test() {
  return T();
}

struct A {
  A();
  A(A &);
  A(int);
  operator int();
};

template A test<A>();

struct BSub {};
struct B : BSub {
  B();
  B(B &);
  B(const BSub &);
};

template B test<B>();
