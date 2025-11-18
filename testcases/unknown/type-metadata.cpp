
// RUN: %driver -cc1 %isys -flto -flto-unit -fvisibility=hidden -fsanitize=cfi-vcall -fsanitize-trap=cfi-vcall %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -flto -flto-unit -fvisibility=hidden -fsanitize=cfi-vcall %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -flto -flto-unit -fvisibility=hidden -fsanitize=cfi-vcall -fsanitize-recover=cfi-vcall %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -flto -flto-unit -fsanitize=cfi-vcall -fsanitize-trap=cfi-vcall %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -flto -flto-unit -fvisibility=hidden -fwhole-program-vtables %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -flto -flto-unit -fwhole-program-vtables %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -flto -flto-unit -fvisibility=hidden -fsanitize=cfi-vcall -fsanitize-trap=cfi-vcall -fwhole-program-vtables %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -flto -flto-unit -fsanitize=cfi-vcall -fsanitize-trap=cfi-vcall -fwhole-program-vtables %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -fexperimental-relative-c++-abi-vtables -flto -flto-unit -fvisibility=hidden -fsanitize=cfi-vcall -fsanitize-trap=cfi-vcall %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexperimental-relative-c++-abi-vtables -flto -flto-unit -fvisibility=hidden -fsanitize=cfi-vcall %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexperimental-relative-c++-abi-vtables -flto -flto-unit -fvisibility=hidden -fsanitize=cfi-vcall -fsanitize-recover=cfi-vcall %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -fexperimental-relative-c++-abi-vtables -flto -flto-unit -fvisibility=hidden -fwhole-program-vtables %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexperimental-relative-c++-abi-vtables -flto -flto-unit -fwhole-program-vtables %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -fexperimental-relative-c++-abi-vtables -flto -flto-unit -fvisibility=hidden -fsanitize=cfi-vcall -fsanitize-trap=cfi-vcall -fwhole-program-vtables %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -fprofile-instrument=llvm -fno-lto %s %target -o %t%output-suffix && %filecheck


// RUN: %driver -cc1 %isys -fprofile-instrument=none -fno-lto %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fprofile-instrument=clang -fno-lto %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fprofile-instrument=csllvm -fno-lto %s %target -o %t%output-suffix && %filecheck












struct A {
  A();
  virtual void f();
};

struct B : virtual A {
  B();
  virtual void g();
  virtual void h();
};

struct C : virtual A {
  C();
};

namespace {

struct D : B, C {
  D();
  virtual void f();
  virtual void h();
};

}

A::A() {}
B::B() {}
C::C() {}
D::D() {}

void A::f() {
}

void B::g() {
}

void D::f() {
}

void D::h() {
}

void af(A *a) {


#line 123
  a->f();
}

void df1(D *d) {
  d->f();
}

void dg1(D *d) {
  d->g();
}

void dh1(D *d) {
  d->h();
}

__attribute__((no_sanitize("cfi")))
void df2(D *d) {
  d->f();
}

__attribute__((no_sanitize("address"))) __attribute__((no_sanitize("cfi-vcall")))
void df3(D *d) {
  d->f();
}

D d;

void foo() {
  df1(&d);
  dg1(&d);
  dh1(&d);
  df2(&d);
  df3(&d);

  struct FA : A {
    void f() {}
  } fa;
  af(&fa);
}

namespace test2 {

struct A {
  virtual void m_fn1();
};
struct B {
  virtual void m_fn2();
};
struct C : B, A {};
struct D : C {
  void m_fn1();
};

void f(D *d) {
  d->m_fn1();
}

}

namespace test3 {
struct E {
  virtual void foo();
};

void g() {
  E e;
  e.foo();
}

}  // Test9




