// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions -std=c++11 %target -o %t%output-suffix && %filecheck

namespace test0 {
  void foo();

  struct A {
    A();
    ~A();
  };

  void test() noexcept {
    A a;
    foo();
  }
}


