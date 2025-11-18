// RUN: %driver -cc1 %isys -std=c++11 -fvisibility-inlines-hidden %s %target -o %t%output-suffix && %filecheck


struct X0 {
  void __attribute__((visibility("default"))) f1() { }
  void f2() { }
  void f3();
  static void f5() { }
  virtual void f6() { }
};

inline void X0::f3() { }

template<typename T>
struct X1 {
  void __attribute__((visibility("default"))) f1() { }
  void f2() { }
  void f3();
  void f4();
  static void f5() { }
  virtual void f6() { }
};

template<typename T>
inline void X1<T>::f3() { }

template<>
inline void X1<int>::f4() { }

struct __attribute__((visibility("default"))) X2 {
  void f2() { }
};

extern template struct X1<float>;

void use(X0 *x0, X1<int> *x1, X2 *x2, X1<float> *x3) {
  x0->f1();
  x0->f2();
  x0->f3();
  X0::f5();
  x0->X0::f6();
  x1->f1();
  x1->f2();
  x1->f3();
  x1->f4();
  X1<int>::f5();
  x1->X1::f6();
  x2->f2();
  x3->f2();
}

namespace test1 {
  struct __attribute__((visibility("default"))) A {
    inline void foo();
    ~A();
  };

  void test() {
    A a;
    a.foo();
  }
}

namespace test2 {
  struct A {};
  template <class T> class B {};
  typedef B<A> arg;

  namespace ns __attribute__((visibility("default"))) {
    template <class T> inline void foo() {}
    extern template void foo<arg>();
  }

  void test() {
    ns::foo<arg>();
  }

}

namespace PR11642 {
  template <typename T>
  class Foo {
  public:
    T foo(T x) { return x; }
  };
  extern template class Foo<int>;
  template class Foo<int>;
}

namespace test3 {
  inline void foo(void) {
  }
  template<typename T>
  inline void zed() {
  }
  template void zed<float>();
  void bar(void) {
    foo();
    zed<int>();
  }
}

namespace test4 {
  extern inline __attribute__ ((__gnu_inline__))
  void foo() {}
  void bar() {
    foo();
  }
}

namespace test5 {
  template <int> inline void Op();
  class UnaryInstruction {
    UnaryInstruction() {
      Op<0>();
    }
  };
  template <int Idx_nocapture> void Op() {
  }
}

namespace test6 {
  template <typename T>
  void f(T x) {
  }
  struct C {
    static void g() {
      f([](){});
    }
  };
  void g() {
    C::g();
  }
}

namespace PR34811 {
  template <typename T> void tf() {}
  
  inline void *f() {
    auto l = []() {};
    return (void *)&tf<decltype(l)>;
  }
  
  void *p = (void *)f;
}
