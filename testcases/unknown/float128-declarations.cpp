// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
/*  Various contexts where type __float128 can appear. The different check
    prefixes are due to different mangling on X86.  */

/*  Namespace */
namespace {
  __float128 f1n;
  __float128 f2n = 33.q;
  __float128 arr1n[10];
  __float128 arr2n[] = { 1.2q, 3.0q, 3.e11q };
  const volatile __float128 func1n(const __float128 &arg) {
    return arg + f2n + arr1n[4] - arr2n[1];
  }
}

/* File */
__float128 f1f;
__float128 f2f = 32.4q;
static __float128 f3f = f2f;
__float128 arr1f[10];
__float128 arr2f[] = { -1.2q, -3.0q, -3.e11q };
__float128 func1f(__float128 arg);

/* Class */
class C1 {
  __float128 f1c;
  static const __float128 f2c;
  volatile __float128 f3c;
public:
  C1(__float128 arg) : f1c(arg), f3c(arg) { }
  __float128 func1c(__float128 arg ) {
    return f1c + arg;
  }
  static __float128 func2c(__float128 arg) {
    return arg * C1::f2c;
  }
};

/*  Template */
template <class C> C func1t(C arg) { return arg * 2.q; }
template <class C> struct S1 {
  C mem1;
};
template <> struct S1<__float128> {
  __float128 mem2;
};

/* Local */
int main(void) {
  __float128 f1l = 123e220q;
  __float128 f2l = -0.q;
  __float128 f3l = 1.189731495357231765085759326628007e4932q;
  C1 c1(f1l);
  S1<__float128> s1 = { 132.q };
  __float128 f4l = func1n(f1l) + func1f(f2l) + c1.func1c(f3l) + c1.func2c(f1l) +
    func1t(f1l) + s1.mem2 - f1n + f2n;
#if (__cplusplus >= 201103L)
  auto f5l = -1.q, *f6l = &f2l, f7l = func1t(f3l);
#endif
  __float128 f8l = f4l++;
  __float128 arr1l[] = { -1.q, -0.q, -11.q };
}

