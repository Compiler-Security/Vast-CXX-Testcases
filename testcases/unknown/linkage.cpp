// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

namespace test1 {
  template <typename T> void f(T) {}
  inline void *g() {
    struct S {
    } s;
    return reinterpret_cast<void *>(f<S>);
  }
  void *h() { return g(); }
}

namespace test2 {
  template <typename T> void f(T) {}
  static inline void *g() {
    struct S {
    } s;
    return reinterpret_cast<void *>(f<S>);
  }
  void *h() { return g(); }
}

namespace test3 {
  template <typename T> void f(T) {}
  void *g() {
    struct S {
    } s;
    return reinterpret_cast<void *>(f<S>);
  }
  void *h() { return g(); }
}

namespace test4 {
  template <typename T> void f(T) {}
  template <int N> inline void *g() {
    struct S {
    } s;
    return reinterpret_cast<void *>(f<S>);
  }
  extern template void *g<1>();
  template void *g<1>();
}

namespace test5 {
  template <typename T> void f(T) {}
  template <int N> inline void *g() {
    struct S {
    } s;
    return reinterpret_cast<void *>(f<S>);
  }
  extern template void *g<1>();
  void *h() { return g<1>(); }
}

namespace test6 {
  template <typename T> void f() {}

  inline void *g() {
    struct S {
      void *h() {
        struct T {
        };
        return (void *)f<T>;
      }
    } s;
    return s.h();
  }

  void *h() { return g(); }
}

namespace test7 {
  template <typename T> void f() {}

  void *g() {
    struct S {
      void *h() {
        struct T {
        };
        return (void *)f<T>;
      }
    } s;
    return s.h();
  }

  void *h() { return g(); }
}

namespace test8 {
  template <typename T> void f(T) {}
  inline void *g() {
    enum S {
    };
    return reinterpret_cast<void *>(f<S>);
  }
  void *h() { return g(); }
}

namespace test9 {
  template <typename T> void f(T) {}
  inline void *g() {
    struct S {
    } s;
    return reinterpret_cast<void *>(f<S*>);
  }
  void *h() { return g(); }
}

namespace test10 {
  template <typename T> void f(T) {}
  inline void *g() {
    struct S {
    } s;
    typedef S(*ftype)();
    return reinterpret_cast<void *>(f<ftype>);
  }
  void *h() { return g(); }
}

namespace test11 {
  namespace {
    struct I {
    };
  }

  template <typename T> void f(T) {}
  inline void *g() {
    struct S {
    };
    typedef S(*ftype)(I * x);
    return reinterpret_cast<void *>(f<ftype>);
  }
  void *h() { return g(); }
}

namespace test12 {
  template <typename T> void foo() {}
  template <typename T> inline void *bar() {
    enum S1 {
    };
    return reinterpret_cast<void *>(foo<S1>);
  }
  inline void *zed() {
    enum S2 {
    };
    return reinterpret_cast<void *>(bar<S2>);
  }
  void *h() { return zed(); }
}

namespace test13 {
  inline void *foo() {
    struct S {
      static void bar() {}
    };
    return (void *)S::bar;
  }
  void *zed() { return foo(); }
}

namespace test14 {
  template <typename T> struct foo {
    template <T *P> static void bar() {}
    static void *g() { return (void *)bar<nullptr>; }
  };
  inline void *f() {
    struct S {
    };
    return foo<S>::g();
  }
  void h() { f(); }
}

namespace test15 {
  template <class T> void zed() {}
  template <class T> void *foo() {
    class bar {
    };
    return reinterpret_cast<void *>(zed<bar>);
  }
  void test() { foo<int>(); }
}

namespace test16 {
  template <class T> void zed() {}
  template <class T> struct foo {
    static void *bar();
  };
  template <class T> void *foo<T>::bar() {
    class S {
    };
    return reinterpret_cast<void *>(zed<S>);
  }
  void *test() { return foo<int>::bar(); }
}

namespace test17 {
  template<int I>
  int *foo() {
    static int bar;
    return &bar;
  }
  template int *foo<42>();
}

namespace test18 {
  template<template<typename> class> struct A {};
  struct B { template<typename> struct C; };
  void f(A<B::C>) {}
}
