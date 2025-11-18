// RUN: %driver -cc1 %isys %s -fms-compatibility %target -o %t%output-suffix && %filecheck

struct S {
  int i;
};

struct M {
  int i;
  int j;
};

class C {
public:
  C() {}

  struct S __attribute__((thiscall)) Small() const {
    struct S s = { 0 };
    return s;
  }

  struct M __attribute__((thiscall)) Medium() const {
    struct M m = { 0 };
    return m;
  }
};

void test( void ) {
  C c;

  (void)c.Small();
  (void)c.Medium();
}
