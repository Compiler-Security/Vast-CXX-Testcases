// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A { int a(); };
typedef int B;
void a() {
  A x;
  ((x.a))();
  ((x.*&A::a))();
  B y;
}
