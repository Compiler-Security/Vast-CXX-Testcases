// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fcxx-exceptions -fexceptions -std=c++03 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fcxx-exceptions -fexceptions -std=c++11 -DCXX11 %s %target -o %t%output-suffix && %filecheck

class X {
public:
  X();
  X(const X&);
  X(const volatile X &);
  ~X();
};

template<typename T> struct Y {
  Y();
  static Y f() {
    Y y;
    return y;
  }
};

void ConsumeX(X x);
extern X OuterX;

X test0() { // http://wg21.link/p2025r2#ex-2
  X x;
  return x; // NRVO happens
}

X test1(bool B) {
  X x;
  if (B)
    return (x); // NRVO happens
  return x;     // NRVO happens
}

X test2(bool B) {
  X x;
  X y;
  if (B)
    return y; // NRVO is impossible
  return x;   // NRVO is impossible
}

X test3(bool B) { // http://wg21.link/p2025r2#ex-4
  if (B) {
    X y;
    return y; // NRVO happens
  }
  X x;
  return x; // FIXME: NRVO could happen, but doesn't
}

extern "C" void exit(int) throw();

X test4(bool B) {
  {
    X x;
    if (B)
      return x; // NRVO happens
  }
  exit(1);
}

#ifdef __EXCEPTIONS
void may_throw();
X test5() { // http://wg21.link/p2025r2#ex-14
  try {
    may_throw();
  } catch (X x) {
    return x; // FIXME: NRVO could happen, but doesn't
  }
}
#endif

X test6() {
  X a __attribute__((aligned(8)));
  return a; // NRVO is impossible
}

X test7(bool b) {
  if (b) {
    X x;
    return x; // NRVO happens
  }
  return X();
}

X test8(bool b) {
  if (b) {
    X x;
    return x; // NRVO happens
  } else {
    X y;
    return y; // NRVO happens
  }
}

Y<int> test9() {
  Y<int>::f();
}

X test10(bool b) { // http://wg21.link/p2025r2#ex-3
  X x;
  if (b)
    return x; // NRVO is impossible
  else
    return X();
}

X test11(bool b) { // http://wg21.link/p2025r2#ex-5
  X x;
  if (b)
    return X();
  return x; // NRVO is impossible
}

X test12(bool b) { // http://wg21.link/p2025r2#ex-6
  do {
    X x;
    if (b)
      break;
    return x; // NRVO happens
  } while (false);
  return X();
}

X test13(bool b) { // http://wg21.link/p2025r2#ex-7
  if (b)
    return X();
  X x;
  return x; // FIXME: NRVO could happen, but doesn't
}

X test14(bool b) { // http://wg21.link/p2025r2#ex-8
  X x;
  if (b)
    return x;
  X y;
  return y; // FIXME: NRVO could happen, but doesn't
}

X test15(bool b) { // http://wg21.link/p2025r2#ex-15
  X x;
  if (b)
    return (x);
  X y;
  return ((y)); // FIXME: NRVO could happen, but doesn't
}

#ifdef CXX11
void test16() { // http://wg21.link/p2025r2#ex-9
  X x;
  ConsumeX([&] {
    X y(x);
    return y; // NRVO happens
  }());
}
#endif

X test17(int i) { // http://wg21.link/p2025r2#ex-10
  if (false) {
  impossible:
    if (i == 3)
      return X();
  }

  while (true) {
    X x;
    if (i == 0)
      return x; // NRVO happens
    if (i == 1)
      break;
    if (i == 2)
      continue;
    if (i == 3)
      goto impossible;
    if (i == 4)
      exit(1);
    if (i == 5)
      return x; // NRVO happens
  }
  return X();
}

X test18(int i) { // http://wg21.link/p2025r2#ex-11
  {
    {
      X x;
      if (i == 0)
        return x; // NRVO happens
    }
    X y;
    if (i == 1)
      return y; // FIXME: NRVO could happen, but doesn't
  }
  X z;
  return z; // FIXME: NRVO could happen, but doesn't
}

#ifdef CXX11
X test19() { // http://wg21.link/p2025r2#ex-12
  X x;
  struct S {
    X f() { return X(); }
  };
  auto L = [&x]() { return X(); }();
  if constexpr (false) {
    return X();
  }
  return x; // NRVO happens
}

template <bool B>
X test20() { // http://wg21.link/p2025r2#ex-18
  X x;
  if constexpr (B) {
    if (false)
      return X();
  }
  return x; // FIXME: NRVO could happen when B == false, but doesn't
}

void test20instantiate() {
  test20<true>();
  test20<false>();
}
#endif

const volatile X test21() { // http://wg21.link/p2025r2#ex-19
  X x;
  return x; // NRVO happens
}

X test22() { // http://wg21.link/p2025r2#ex-19
  volatile X x;
  return x; // NRVO is impossible
}

X test23(bool b) { // http://wg21.link/p2025r2#ex-19
  if (b) {
    const X x;
    return x; // NRVO happens
  }
  volatile X y;
  return y; // NRVO is impossible
}

#ifdef __EXCEPTIONS
X test24() { // http://wg21.link/p2025r2#ex-20
  X x;
  if (&x == &OuterX)
    throw 0;
  return x; // NRVO happens
}
#endif

#ifdef CXX11
template <bool B>
X test25() {
  X x;
  if constexpr (B) {
    return x; // FIXME: NRVO could happen when B == true, but doesn't
  } else {
    return X();
  }
}

void test25instantiate() {
  test25<true>();
  test25<false>();
}
#endif
