// RUN: %driver -cc1 %isys -std=c++11 -I%S %s %target -o %t%output-suffix && %filecheck

#include <typeinfo>

int* a = nullptr;

void f() {
  int* a = nullptr;
}

typedef decltype(nullptr) nullptr_t;

nullptr_t get_nullptr();

struct X { };
void g() {
  int (X::*pmf)(int) = get_nullptr();
}

const std::type_info& f2() {
  return typeid(nullptr_t);
}

union U {
  int n;
  nullptr_t b;
};
bool pr23833_a(U &u) { return bool(u.b); }

nullptr_t pr23833_b(nullptr_t &n) { return n; }

struct X1 { operator int*(); };
struct X2 { operator const nullptr_t&(); };

int pr23833_c() {
  return X1() != X2();
}

int *pr23833_d() {
  int *p = X2();
  return p;
}

namespace PR39528 {
  constexpr nullptr_t null = nullptr;
  void f(nullptr_t);
  void g() { f(null); }
}
