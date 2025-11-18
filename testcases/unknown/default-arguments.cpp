// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace PR5484 {
struct A { };
extern A a;

void f(const A & = a);

void g() {
  f();
}
}

struct A1 {
 A1();
 ~A1();
};

struct A2 {
 A2();
 ~A2();
};

struct B {
 B(const A1& = A1(), const A2& = A2());
};

void f1() {

 B bs[2];
}

struct C {
 B bs[2];
 C();
};


C::C() { }

void f3() {
 B *bs = new B[2];
 delete bs;
}

void f4() {
  void g4(int a, int b = 7);
  {
    void g4(int a, int b = 5);
  }
  void g4(int a = 5, int b);

  g4();
}
