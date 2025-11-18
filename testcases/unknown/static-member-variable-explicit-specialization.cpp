// RUN: %driver -cc1 %isys %s -std=c++1y %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++1y -fdeclspec -DSELECTANY %target -o %t%output-suffix && %filecheck

#ifdef SELECTANY
struct S {
  S();
  ~S();
};

int f();

int __declspec(selectany) selectany = f();

#else


extern "C" int foo();

template<typename T> struct A { static int a; };
template<typename T> int A<T>::a = foo();

template<> int A<char>::a;

template<> int A<bool>::a = 10;



















template int A<short>::a;  // Unordered
int b = foo();
int c = foo();
int d = A<void>::a; // Unordered

template<> struct A<int> { static int a; };
int A<int>::a = foo();

template<typename T> struct S { static T x; static T y; };
template<> int S<int>::x = foo();
template<> int S<int>::y = S<int>::x;

template<typename T> T x = foo();
template short x<short>;  // Unordered
template<> int x<int> = foo();
int e = x<char>; // Unordered

namespace ns {
template <typename T> struct a {
  static int i;
};
template<typename T> int a<T>::i = foo();
template struct a<int>;

struct b {
  template <typename T> static T i;
};
template<typename T> T b::i = foo();
template int b::i<int>;
}

namespace {
template<typename T> struct Internal { static int a; };
template<typename T> int Internal<T>::a = foo();
}
int *use_internal_a = &Internal<int>::a;

template<int n> struct Fib { static int a; };
template<> int Fib<0>::a = 0;
template<> int Fib<1>::a = 1;
template<int n> int Fib<n>::a = Fib<n-2>::a + Fib<n-1>::a;
int f = Fib<5>::a;

template<int n> struct Fib2 { static int a; };
template<> int Fib2<0>::a = 0;
template<> int Fib2<1>::a = 1;
template<int n> int Fib2<n>::a = Fib2<n-1>::a + Fib2<n-2>::a;
int f2 = Fib2<5>::a;

#endif















