// RUN: %driver -std=c++11 %s %target -S -o %t%output-suffix && %filecheck

/*  Various contexts where type _Float16 can appear. */


/*  Namespace */

namespace {
  _Float16 f1n;

  _Float16 f2n = 33.f16;

  _Float16 arr1n[10];

  _Float16 arr2n[] = { 1.2, 3.0, 3.e4 };

  const volatile _Float16 func1n(const _Float16 &arg) {
    return arg + f2n + arr1n[4] - arr2n[1];
  }
}


/* File */

_Float16 f1f;

_Float16 f2f = 32.4;

_Float16 arr1f[10];

_Float16 arr2f[] = { -1.2, -3.0, -3.e4 };

_Float16 func1f(_Float16 arg);


/* Class */

class C1 {
  _Float16 f1c;

  static const _Float16 f2c;

  volatile _Float16 f3c;

public:
  C1(_Float16 arg) : f1c(arg), f3c(arg) { }

  _Float16 func1c(_Float16 arg ) {
    return f1c + arg;
  }

  static _Float16 func2c(_Float16 arg) {
    return arg * C1::f2c;
  }
};

/*  Template */

template <class C> C func1t(C arg) {
  return arg * 2.f16;
}

template <class C> struct S1 {
  C mem1;
};

template <> struct S1<_Float16> {
  _Float16 mem2;
};


/* Local */

extern int printf (const char *__restrict __format, ...);

int main(void) {
  _Float16 f1l = 1e3f16;

  _Float16 f2l = -0.f16;

  _Float16 f3l = 1.000976562;

  C1 c1(f1l);

  S1<_Float16> s1 = { 132.f16 };

  _Float16 f4l = func1n(f1l)  + func1f(f2l) + c1.func1c(f3l) + c1.func2c(f1l) +
    func1t(f1l) + s1.mem2 - f1n + f2n;

  auto f5l = -1.f16, *f6l = &f2l, f7l = func1t(f3l);

  _Float16 f8l = f4l++;

  _Float16 arr1l[] = { -1.f16, -0.f16, -11.f16 };

  float cvtf = f2n;

  double cvtd = f2n;


  long double cvtld = f2n;

  _Float16 f2h = 42.0f;
  _Float16 d2h = 42.0;
  _Float16 ld2h = 42.0l;
}
