// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A { int x; int y[]; };
A a = { 1, 7, 11 };

A b = { 1, { 13, 15 } };

char f();
#ifdef FAIL1
A c = { f(), { f(), f() } }; // expected-error {{cannot compile this flexible array initializer yet}}
#endif
#ifdef FAIL2
void g() {
  static A d = { f(), { f(), f() } }; // expected-error {{cannot compile this flexible array initializer yet}}
}
#endif
#ifdef FAIL3
struct B { int x; char y; char z[]; };
B e = {f(), f(), f(), f()}; // expected-error {{cannot compile this flexible array initializer yet}}
#endif

namespace zero_initializer {
A a0{0, 0}, a1{0, {0, 0}};

struct S { int x[]; };

S s{0};
}
