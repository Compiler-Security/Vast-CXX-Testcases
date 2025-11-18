// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct A { 
  void f(); 
  
  int a;
};

struct B : A { 
  double b;
};

void f() {
  B b;
  
  b.f();
}

B *f(A *a) {
  return static_cast<B*>(a);
}

namespace PR5965 {

A *f(B* b) {
  return b;
}

}

namespace test3 {
  struct A {};
  struct B : A {};

  void foo(A a);
  void test() {
    foo(B());
  }
}

