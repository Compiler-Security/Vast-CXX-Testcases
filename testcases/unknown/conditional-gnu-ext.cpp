// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);

void test0() {
    printf("%p\n", (void *)0xdeadbeef ? : (void *)0xaaaaaa);
}

namespace radar8446940 {
extern "C" void abort();

int main () {
  char x[1];
  char *y = x ? : 0;

  if (x != y)
    abort();
}
}

namespace radar8453812 {
extern "C" void abort();
_Complex int getComplex(_Complex int val) {
  static int count;
  if (count++)
    abort();
  return val;
}

_Complex int cmplx() {
    _Complex int cond;
    _Complex int rhs;

    return getComplex(1+2i) ? : rhs;
}

void foo (int& lv) {
  ++lv;
}

int global = 1;

int &cond() {
  static int count;
  if (count++)
    abort();
  return global;
}


int main() {
  cmplx();
  int rhs = 10;
  foo (cond()? : rhs);
  return  global-2;
}
}

namespace test3 {
  struct A {
    A();
    A(const A&);
    ~A();
  };

  struct B {
    B();
    B(const B&);
    ~B();
    operator bool();
    operator A();
  };

  B test0(B &x) {
    return x ?: B();
  }

  B test1() {
    extern B test1_helper();
    return test1_helper() ?: B();
  }


  A test2(B &x) {
    return x ?: A();
  }

  A test3() {
    extern B test3_helper();
    return test3_helper() ?: A();
  }

}

namespace test4 {
  void f() {
    const int a = 10, b = 20;
    const int *c = &(a ?: b);
  }
}
