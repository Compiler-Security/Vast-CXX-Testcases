// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace test0 {

  int test1(...) {
    return -1;
  }

  void test() {
    test1(0);
  }
}

namespace test1 {
  struct A {
    int x;
    int y;
  };

  void foo(...);

  void test() {
    A x;
    foo(x);
  }
}
