// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct C {
  void f();
  void g(int, ...);
};

void C::f() {
}

void test1() {
  C c;

  c.f();

  c.g(1, 2, 3);
}


struct S {
  inline S() { }
  inline ~S() { }

  void f_inline1() { }
  inline void f_inline2() { }

  static void g() { }
  static void f();

  virtual void v() {}
};

void S::f() {
}

void test2() {
  S s;

  s.f_inline1();
  s.f_inline2();

  S::g();
}






struct T {
  T operator+(const T&);
};

void test3() {
  T t1, t2;

  T result = t1 + t2;
}



