// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck



namespace test1 {
  struct A {
    static const int a = 10;
  };

  const int A::a;

  struct S { 
    static int i;
  };

  void f() { 
    int a = S::i;
  }
}

namespace test2 {
  int foo();

  namespace {
    template <class T> struct A {
      static int x;
    };

    template <class T> int A<T>::x = foo();
    template struct A<int>;
  }

}

namespace test3 {
  int foo();

  template <class T> struct A {
    static int x;
  };

  template <class T> int A<T>::x = foo();
  template struct A<int>;

}

namespace test4 {
  struct A {
    static const int n = 76;
  };

  int f(A *a) {
    return a->n;
  }
}

namespace test5 {
  union U {
    static int k0;
    static const int k1;
    static const int k2 = 76;
    static const int k3;
    static const int k4 = 81;
  };
  int U::k0;
  const int U::k1 = (k0 = 9, 42);
  const int U::k2;

}
