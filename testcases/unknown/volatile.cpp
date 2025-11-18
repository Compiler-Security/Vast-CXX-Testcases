// RUN: %driver -cc1 %isys %s -std=c++98 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

namespace test0 {
  struct A {
    A(const A& t);
    A& operator=(const A& t);
    volatile A& operator=(const volatile A& t) volatile;
  };

  volatile A *array;

  void test(A t) {
    array[0] = t;
  }
}

namespace test1 {
  volatile int *x;

  void test() {
    *x;
  }
}

namespace PR40642 {
  template <class T> struct S {
    void foo() {
      if (true)
        reinterpret_cast<const volatile unsigned char *>(m_ptr)[0];
    }
    int *m_ptr;
  };

  void f(S<int> *x) { x->foo(); }
}
