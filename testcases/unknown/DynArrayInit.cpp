// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

inline void* operator new[](unsigned long, void* __p)  { return __p; }
static void f0_a(char *a) {
  new (a) char[4]();
}
char f0() {
  char a[4];
  f0_a(a);
  return a[0] + a[1] + a[2] + a[3];
}
