// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

struct alignas(8) AM8 {
  int f1, f2;
};
AM8 m8;
AM8 load8() {
  AM8 am;
  __atomic_load(&m8, &am, 0);
  return am;
}

AM8 s8;
void store8() {
  __atomic_store(&m8, &s8, 0);
}

bool cmpxchg8() {
  AM8 am;
  return __atomic_compare_exchange(&m8, &s8, &am, 0, 0, 0);
}

struct alignas(16) AM16 {
  long f1, f2;
};

AM16 m16;
AM16 load16() {
  AM16 am;
  __atomic_load(&m16, &am, 0);
  return am;
}

AM16 s16;
void store16() {
  __atomic_store(&m16, &s16, 0);
}

bool cmpxchg16() {
  AM16 am;
  return __atomic_compare_exchange(&m16, &s16, &am, 0, 0, 0);
}
