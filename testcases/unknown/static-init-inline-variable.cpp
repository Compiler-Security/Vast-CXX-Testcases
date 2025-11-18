// RUN: %driver -cc1 %isys -std=c++17 %s %target -o %t%output-suffix && %filecheck

struct A {
  int x;
  A(int x) : x(x) {}
  ~A() {}
};

namespace DeferredSequence {
inline int a = 1;
inline int b = a + 1;
inline int c = b + 1;
inline int d = c + 1;
int e = d;
}

namespace MixedSequence {
inline A a(1);
inline int x = a.x + 1;
inline int y = x + 1;
inline A b(y);
inline int z = b.x + 1;
inline int w = z + 1;
inline A c(b.x);
inline A d(c.x);
int t = w;
}

namespace NonDeferredSequence {
inline A a(1);
inline A b(a.x);
inline A c(b.x);
inline A d(c.x);
}

