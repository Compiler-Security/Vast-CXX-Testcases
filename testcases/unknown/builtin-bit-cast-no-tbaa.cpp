// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck

void test_scalar() {
  __builtin_bit_cast(float, 42);

}

void test_scalar2() {
  struct S {int m;};
  __builtin_bit_cast(int, S{42});

}

int test_same_type(int &r) {
  return __builtin_bit_cast(int, r);
}

