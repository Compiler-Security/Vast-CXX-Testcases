// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

class x {
public: int operator=(int);
};
void a() {
  x a;
  a = 1u;
}

void f(int i, int j) {
  (i += j) = 17;
}

namespace test1 {
  template <class T> void fn (T t) { }
  template <class T> struct A {
    void (*p)(T);
    A() { p = fn; }
  };

  A<int> a;
}

struct A {
  A &operator=(const A&);
};
struct B {
  B(const B&);
  B &operator=(const B&) = default;
  int n;
};
struct C {
  A a;
  B b[16];
};
void b(C &a, C &b) {
  a = b;
}
