// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -femulated-tls %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++11 -fno-use-cxa-atexit %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -fno-use-cxa-atexit -femulated-tls %s %target -o %t%output-suffix && %filecheck

int f();
int g();

thread_local int a = f();
extern thread_local int b;
int c = b;
static thread_local int d = g();

struct U { static thread_local int m; };
thread_local int U::m = f();

namespace MismatchedInitType {
  union U {
    int a;
    float f;
    constexpr U() : f(0.0) {}
  };
  static thread_local U u;
  void *p = &u;
}

template<typename T> struct V { static thread_local int m; };
template<typename T> thread_local int V<T>::m = g();

template<typename T> struct W { static thread_local int m; };
template<typename T> thread_local int W<T>::m = 123;

struct Dtor { ~Dtor(); };
template<typename T> struct X { static thread_local Dtor m; };
template<typename T> thread_local Dtor X<T>::m;

void *e = V<int>::m + W<int>::m + &X<int>::m;

template thread_local int V<float>::m;
template thread_local int W<float>::m;
template thread_local Dtor X<float>::m;

extern template thread_local int V<char>::m;
extern template thread_local int W<char>::m;
extern template thread_local Dtor X<char>::m;

void *e2 = V<char>::m + W<char>::m + &X<char>::m;














int f() {

  static thread_local int n = g();

  return n;
}















struct S { S(); ~S(); };
struct T { ~T(); };

void tls_dtor() {
  static thread_local S s;

  static thread_local T t;

  static thread_local const S &u = S();
}




int PR15991() {
  thread_local int n;
  auto l = [] { return n; };
  return l();
}

struct PR19254 {
  static thread_local int n;
  int f();
};
int PR19254::f() {
  return this->n;
}

namespace {
thread_local int anon_i{f()};
}
void set_anon_i() {
  anon_i = 2;
}













