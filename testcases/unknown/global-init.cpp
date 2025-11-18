// RUN: %driver -cc1 %isys %std_cxx98-14 -fexceptions %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %std_cxx98-14 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %std_cxx98-14 -mframe-pointer=non-leaf %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %std_cxx98-14 %s -fno-builtin %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %std_cxx17- -fexceptions %s %target -o %t%output-suffix && %filecheck

struct A {
  A();
  ~A();
};

struct B { B(); ~B(); };

struct C { void *field; };

struct D { ~D(); };



A a;

B b;

C c;

D d;

namespace test1 {
  int f();
  const int x = f();   // This has side-effects and gets emitted immediately.
  const int y = x - 1; // This gets deferred.
  const int z = ~y;    // This also gets deferred, but gets "undeferred" before y.
  int test() { return z; }

}

namespace test2 {
  struct allocator { allocator(); ~allocator(); };
  struct A { A(const allocator &a = allocator()); ~A(); };

  A a;
}

namespace test3 {
  const char * const var = "string";
  extern const char * const var;

  const char *test() { return var; }
}

namespace test4 {
  struct A {
    A();
  };
  extern int foo();

  __attribute__((weak)) int x = foo();
}

namespace PR5974 {
  struct A { int a; };
  struct B { int b; };
  struct C : A, B { int c; };

  extern C c;

  A* a = &c;
  B* b = &c;
}

namespace test5 {
  static union {
    unsigned bar[4096] __attribute__((aligned(128)));
  };
}

namespace std { struct type_info; }

namespace test6 {
  struct A { virtual ~A(); };
  struct B : A {};
  extern A *p;

  B *const q = &dynamic_cast<B&>(*p);

  B *const r = dynamic_cast<B*>(p);

  const std::type_info *const s = &typeid(*p);

  const std::type_info *const t = &typeid(p);

  extern B *volatile v;
  B *const w = dynamic_cast<B*>(v);

  const int x = *(volatile int*)0x1234;

  namespace {
    int a = int();
    volatile int b = int();
    int c = a;
    int d = b;
  }
}

namespace test7 {
  struct A { A(); };
  struct B { ~B(); int n; };
  struct C { C() = default; C(const C&); int n; };
  struct D {};

  const A a = A();

  const B b1 = B();
  const B &b2 = B();
  const int b3 = B().n;

  const C c1 = C();
  const C c2 = static_cast<const C&>(C());
  const int c3 = C().n;
  const int c4 = C(C()).n;

  const D d = D();

  int f(), e = f();
}







