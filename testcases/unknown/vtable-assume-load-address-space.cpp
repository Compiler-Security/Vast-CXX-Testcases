// RUN: %driver -cc1 %isys %s -std=c++11 -fms-extensions -fstrict-vtable-pointers %target -o %t%output-suffix && %filecheck

namespace test1 {

struct A {
  A();
  virtual void foo();
};

struct B : A {
  virtual void foo();
};

void g(A *a) { a->foo(); }


void fooA() {
  A a;
  g(&a);
}


void fooB() {
  B b;
  g(&b);
}
}
namespace test2 {
struct A {
  A();
  virtual void foo();
};

struct B {
  B();
  virtual void bar();
};

struct C : A, B {
  C();
  virtual void foo();
};
void g(A *a) { a->foo(); }
void h(B *b) { b->bar(); }




void test() {
  C c;
  g(&c);
  h(&c);
}
}

namespace test3 {
struct A {
  A();
};

struct B : A {
  B();
  virtual void foo();
};

struct C : virtual A, B {
  C();
  virtual void foo();
};
void g(B *a) { a->foo(); }

void test() {
  C c;
  g(&c);
}
} // test3

namespace test4 {
struct A {
  A();
  virtual void foo();
};

struct B : virtual A {
  B();
  virtual void foo();
};
struct C : B {
  C();
  virtual void foo();
};

void g(C *c) { c->foo(); }



void test() {
  C c;
  g(&c);
}
} // test4

namespace test6 {
struct A {
  A();
  virtual void foo();
  virtual ~A() {}
};
struct B : A {
  B();
};


void g() {
  A *a = new A;
  B *b = new B;
}
}

namespace test7 {
struct A {
  A();
  virtual void foo();
  virtual void bar();
};
void A::foo() {}

void g() {
  A *a = new A();
  a->bar();
}
}

namespace test8 {

struct A {
  virtual void foo();
  virtual void bar();
};

struct B : A {
  B();
  void foo();
  void bar();
};

struct C : A {
  C();
  void bar();
  void foo() {}
};
inline void C::bar() {}

struct D : A {
  D();
  void foo();
  void inline bar();
};
void D::bar() {}

struct E : A {
  E();
};

void b() {
  B b;
  b.bar();
}

void c() {
  C c;
  c.bar();
}

void d() {
  D d;
  d.bar();
}

void e() {
  E e;
  e.bar();
}
}

namespace test9 {

struct S {
  S();
  __attribute__((visibility("hidden"))) virtual void doStuff();
};

void test() {
  S *s = new S();
  s->doStuff();
  delete s;
}
}

