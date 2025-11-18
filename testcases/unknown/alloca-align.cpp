// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct s0 {
  int Start, End;
  unsigned Alignment;
  int TheStores __attribute__((aligned(16)));
};

extern "C" void f0() {
  (void) s0();
}

extern "C" void f1() {
  (void) (struct s0) { 0, 0, 0, 0 };
}

struct s1 { short x; short y; };
extern "C" struct s1 f2(int a, struct s1 *x, struct s1 *y) {
  if (a)
    return *x;
  return *y;
}
