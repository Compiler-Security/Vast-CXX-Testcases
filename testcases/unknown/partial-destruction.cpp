// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions -std=c++03 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions -std=c++11 %target -o %t%output-suffix && %filecheck


void opaque();

namespace test0 {
  struct A { A(int); A(); ~A(); void *v; };
  void test() {
    A as[10] = { 5, 7 };
    opaque();
  }








}

namespace test1 {
  struct A { A(); A(int); ~A(); };
  struct B { A x, y, z; int w; };

  void test() {
    B v = { 5, 6, 7, 8 };
  }

}

namespace test2 {
  struct A { A(); ~A(); };

  void test() {
    A v[4][7];



  }

}

namespace test3 {
  struct A { A(); ~A(); void *p; };
  struct B {
    B() {}
    A a;
  };

  B *test() {
    return new B[10];
  }
}

namespace test4 {
  struct A { A(unsigned i); ~A(); };
  void test() {
    A v[2][3] = { { A(0), A(1), A(2) }, { A(3), A(4), A(5) } };
  }
}
