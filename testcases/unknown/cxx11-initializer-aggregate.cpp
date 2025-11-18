// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 %s %target -o %t%output-suffix && %filecheck

struct A { int a, b; int f(); };

namespace NonAggregateCopyInAggregateInit { // PR32044
  struct A { constexpr A(int n) : x(n), y() {} int x, y; } extern a;
  struct B { A &p; } b{{a}};
  struct C { A &&p; } c{{1}};
}

namespace NearlyZeroInit {
  int a[123] = {1, 2, 3};
  struct B { int n; int arr[1024 * 1024 * 1024 * 2u]; } b = {1, {2}};
}

namespace PR37560 {
  union U {
    char x;
    int a;
  };
  U c[1] = {};
  U d[16] = {'a', {.a = 123}, 'b'};
  U e[16] = {{.a = 123}, {.a = 456}};

  union V {
    int a;
    char x;
  };
  V f[1] = {};
  V g[16] = {{.x = 'a'}, {.a = 123}, {.x = 'b'}};
  V h[16] = {{.a = 123}, {.a = 456}};
  V i[4] = {{.a = 123}, {.a = 456}};
}

int fn1(int x) {
  return A{x, 5}.f();
}

struct B { int &r; int &f() { return r; } };

int &fn2(int &v) {
  return B{v}.f();
}

namespace NonTrivialInit {
  struct A { A(); A(const A&) = delete; ~A(); };
  struct B { A a[20]; };
  B b[30] = {};
}

namespace ZeroInit {
  enum { Zero, One };
  constexpr int zero() { return 0; }
  constexpr int *null() { return nullptr; }
  struct Filler {
    int x;
    Filler();
  };
  struct S1 {
    int x;
  };

  unsigned char data_1[1024 * 1024 * 1024 * 2u] = { 0 };
  unsigned char data_2[1024 * 1024 * 1024 * 2u] = { Zero };
  unsigned char data_3[1024][1024][1024] = {{{0}}};
  unsigned char data_4[1024 * 1024 * 1024 * 2u] = { zero() };
  int *data_5[1024 * 1024 * 512] = { nullptr };
  int *data_6[1024 * 1024 * 512] = { null() };
  struct S1 data_7[1024 * 1024 * 512] = {{0}};
  char data_8[1000 * 1000 * 1000] = {};
  int (&&data_9)[1000 * 1000 * 1000] = {0};
  unsigned char data_10[1024 * 1024 * 1024 * 2u] = { 1 };
  unsigned char data_11[1024 * 1024 * 1024 * 2u] = { One };
  unsigned char data_12[1024][1024][1024] = {{{1}}};

  Filler data_e1[1024] = {};

  struct Largeish {
    long a, b, c;
  };
  Largeish largeish1() { return {}; }
  Largeish largeish2() { return Largeish(); }
  Largeish largeish3() { return Largeish{}; }
  Largeish largeish4() { return (Largeish){}; }
  Largeish largeish5() { return {0, 0, 0}; }

  typedef __attribute__((ext_vector_type(4))) char CI4;
  struct Conversions {
    _Complex int a;
    _Complex float b;
    short c;
    long double d;
    CI4 e;
    char f;
    char g;
    int *h;
    long i;
  };
  Conversions conversions() {
    return {0,
            0,
            0,
            0,
            CI4(0),
            static_cast<char>(0.0),
            char(0 + 0i),
            reinterpret_cast<int *>(0),
            reinterpret_cast<long>((int *)nullptr)};
  }
}
