// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++98 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

int a = 10;
int &ar = a;

void f();
void (&fr)() = f;

struct S { int& a; };
S s = { a };

namespace PR5581 {
class C {
public:
  enum { e0, e1 };
  unsigned f;
};

C g0 = { C::e1 };
}

namespace test2 {
  struct A {
#if __cplusplus <= 199711L
    static const double d = 1.0;
    static const float f = d / 2;
#else
    static constexpr double d = 1.0;
    static constexpr float f = d / 2;
#endif
    static int g();
  } a;

  double t0 = A::d;
  double t1[] = { A::d, A::f };
  const double *t2 = &a.d;
  int (*t3)() = &a.g;
}

float PR9558 = reinterpret_cast<const float&>("asd");

struct MutableMember {
  mutable int n;
};
int writeToMutable() {
  const MutableMember MM = { 0 };
  return ++MM.n;
}

__int128_t PR11705 = (__int128_t)&PR11705;

void UnfoldableAddrLabelDiff() { static __int128_t x = (long)&&a-(long)&&b; a:b:return;}

// void FoldableAddrLabelDiff() { static long x = (long)&&a-(long)&&b; a:b:return;}

int &i = reinterpret_cast<int&>(PR9558);

int arr[2];
int &pastEnd = arr[2];

wchar_t *PR51105_a = (wchar_t[2]){ (L"p") };
char *PR51105_b = (char [5]){ ("p") };

struct X {
  long n : 8;
};
long k;
X x = {(long)&k};
