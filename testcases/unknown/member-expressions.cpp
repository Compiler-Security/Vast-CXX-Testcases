// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace PR5392 {
struct A
{
  static int a;
};

A a1;
void f()
{
  a1.a = 10;
  A().a = 20;
}

}

struct A {
  A();
  ~A();
  enum E { Foo };
};

A *g();

void f(A *a) {
  A::E e1 = a->Foo;
  
  A::E e2 = g()->Foo;
  A::E e3 = A().Foo;
}

namespace test3 {
struct A {
  static int foo();
};
int f() {
  return A().foo();
}
}

namespace test4 {
  struct A {
    int x;
  };
  struct B {
    int x;
    void foo();
  };
  struct C : A, B {
  };

  extern C *c_ptr;

  int test() {
    c_ptr->B::foo();

    c_ptr->B::x = 5;

    return c_ptr->B::x;
  }
}
