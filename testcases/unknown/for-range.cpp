// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct A {
  A();
  A(const A&);
  ~A();
};

struct B {
  B();
  B(const B&);
  ~B();
};

struct C {
  C();
  C(const C&);
  ~C();
};

struct D {
  D();
  D(const D&);
  ~D();

  B *begin();
  B *end();
};

B *begin(C&);
B *end(C&);

extern B array[5];

void for_array() {
  A a;
  for (B b : array) {
  }
}

void for_range() {
  A a;
  for (B b : C()) {
  }
}

void for_member_range() {
  A a;
  for (B b : D()) {
  }
}
