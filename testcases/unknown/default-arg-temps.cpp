// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct T {
  T();
  ~T();
};

void f(const T& t = T());

class X { // ...
public:
        X();
        X(const X&, const T& t = T());
};

void g() {
  f();

  f();

  X a;

  X b(a);

  X c = a;
}


class obj{ int a; float b; double d; };
void h() {
  obj o = obj();
}

namespace test1 {
  struct A { A(); };
  struct B { B(); ~B(); };

  struct C {
    C(const B &file = B());
  };
  C::C(const B &file) {}

  struct D {
    C c;
    A a;

    D() : c(), a() {}
  };

  D d;
}

namespace test2 {
  template <typename T> struct A { A() {} ~A() {} };
  template <typename> void f(const A<int> & = {}) {}
  void g() { f<int>(); }
}
