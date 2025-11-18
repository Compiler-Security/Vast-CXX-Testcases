// RUN: %driver -cc1 %isys -x c++ < %s %target -o %t%output-suffix && %filecheck

void test0(int x) {
          if (x != 0) return;
}


void test1() {
  char *xpto;
  while ( true && xpto[0] );
}

int a;
void test2() { ++a+=10; }

int test3(const char*);
int test3g = test3(__PRETTY_FUNCTION__);


struct test4A {
  int j : 2;
};
int test4() {
  test4A a;
  (a.j = 2) = 3;
}

struct s5;
struct s5 &f5_0(bool cond, struct s5 &a, struct s5 &b) {
  return cond ? a : b;
}
