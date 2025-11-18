// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions -std=c++98 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions -std=c++11 %target -o %t%output-suffix && %filecheck

namespace test0 {
  struct A { A(); ~A(); };
  struct V { V(const A &a = A()); ~V(); };

  template<int X> int test(int x) {

    A y;
    try {
      A z;
      V *v = new V();

      if (x) return 1;
    } catch (int ex) {
      return 1;
    }
    return 0;
  }

  int test() {
    return test<0>(5);
  }
}
