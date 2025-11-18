// RUN: %driver -cc1 %isys -std=c++11 %s -Wno-address-of-temporary %target -o %t%output-suffix && %filecheck


struct A { int a[1]; };
typedef A x[];
int f() {
  x{{{1}}};
  return 0;
}

namespace ValueInitArrayOfMemPtr {
  struct S {};
  typedef int (S::*p);
  typedef p a[3];
  void f(const a &);

  struct Agg1 {
    int n;
    p x;
  };

  struct Agg2 {
    int n;
    a x;
  };

  struct S1 {
    p x;
    S1();
  };

  void f(int n) {
    Agg1 a = { n };

    Agg2 b = { n };
  }

  void g(p ptr) {
    f(a{ptr});
  }
}

namespace array_dtor {
  struct S { S(); ~S(); };
  using T = S[3];
  void f(const T &);
  void f(T *);
  void g() {



    f(T{});

  }
  void h() {

    T &&t = T{};

    f(t);


  }
  void i() {



    f(&T{});

  }
}
