// RUN: %driver -cc1 %isys %s -I%S %target -o %t%output-suffix && %filecheck

#include <typeinfo>

namespace Test1 {
  struct __attribute__((visibility("hidden"))) A { };

  void f() {
    (void)typeid(A);
    (void)typeid(A *);
  }
}

namespace Test2 {
  struct A { };
  void f() {
    (void)typeid(A);
  }
}
