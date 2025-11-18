// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

union Test1 {
  int a;
  int b: 39;
};
Test1 t1;

union Test2 {
  int : 6;
} t2;

union Test3 {
  int : 9;
} t3;

union Test4 {
  char val : 16;
};
Test4 t4;

#define CHECK(x) if (!(x)) return __LINE__

int test_assign() {
  struct {
    int a;

    unsigned long long b : 65;

    int c;
  } c;
  
  c.a = 0;
  c.b = (unsigned long long)-1;
  c.c = 0;

  CHECK(c.a == 0);
  CHECK(c.b == (unsigned long long)-1);
  CHECK(c.c == 0);

  Test1 u1;
  Test4 u2;

  u1.b = 1;
  u2.val = 42;

  CHECK(u1.b == 1);
  CHECK(u2.val == 42);

  return 0;
}

int test_init() {
  struct S {
    int a;

    unsigned long long b : 65;

    int c;
  };
  S s1 = {1, 42, 0};

  CHECK(s1.a == 1);
  CHECK(s1.b == (unsigned long long)42);
  CHECK(s1.c == 0);

  Test1 u1 = {1};
  Test4 u2 = {42};

  CHECK(u1.a == 1);
  CHECK(u1.b == 1);
  CHECK(u2.val == 42);

  return 0;
}

extern "C" {
int test_trunc_int() {
  union {
    int i : 4; // truncated to 0b1111 == -1
  } const U = {15};  // 0b00001111
  return U.i;
}

int test_trunc_three_bits() {
  union {
    int i : 3; // truncated to 0b111 == -1
  } const U = {15};  // 0b00001111
  return U.i;
}

int test_trunc_one_bit() {
  union {
    int i : 1; // truncated to 0b1 == -1
  } const U = {1};  // 0b00000001
  return U.i;
}

int test_trunc_1() {
  union {
    int i : 1; // truncated to 0b1 == -1
  } const U = {15};  // 0b00001111
  return U.i;
}

int test_trunc_zero() {
  union {
    int i : 4; // truncated to 0b0000 == 0
  } const U = {80};  // 0b01010000
  return U.i;
}

int test_constexpr() {
  union {
    int i : 3;           // truncated to 0b111 == -1
  } const U = {1 + 2 + 4 + 8}; // 0b00001111
  return U.i;
}

int test_notrunc() {
  union {
    int i : 12;          // not truncated
  } const U = {1 + 2 + 4 + 8}; // 0b00001111
  return U.i;
}

long long test_trunc_long_long() {
  union {
    long long i : 14; // truncated to 0b00111101001101 ==
  } const U = {0b0100111101001101};
  return U.i;
}
}
