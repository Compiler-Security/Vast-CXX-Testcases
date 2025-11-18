// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -fclang-abi-compat=6.0 %target -o %t%output-suffix && %filecheck

extern int int_source();
extern void int_sink(int x);

namespace test0 {
  struct A {
    int aField;
    int bField;
  };

  struct B {
    int onebit : 2;
    int twobit : 6;
    int intField;
  };

  struct __attribute__((packed, aligned(2))) C : A, B {
  };

  void a(B &b) {
    b.onebit = int_source();

    int_sink(b.onebit);
  }

  void b(C &c) {
    c.onebit = int_source();

    int_sink(c.onebit);
  }

  void c(C *c) {
    c->onebit = int_source();

    int_sink(c->onebit);
  }

  void d() {
    C c;

    c.onebit = int_source();

    int_sink(c.onebit);
  }

  void e() {
    __attribute__((aligned(16))) C c;

    c.onebit = int_source();

    int_sink(c.onebit);
  }
}

namespace test1 {
  struct Array {
    int elts[4];
  };

  struct A {
    __attribute__((aligned(16))) Array aArray;
  };

  struct B : virtual A {
    void *bPointer; // puts bArray at offset 16
    Array bArray;
  };

  struct C : virtual A { // must be viable as primary base
    void *cPointer1;
    void *cPointer2;
  };

  struct D : C, B {};

  typedef __attribute__((aligned(64))) Array AlignedArray;

  void a(A &a) {
    AlignedArray result = a.aArray;
  }

  void b(B &b) {
    AlignedArray result = b.aArray;
  }

  void c(B &b) {
    AlignedArray result = b.bArray;
  }

  void d(B *b) {
    AlignedArray result = b->bArray;
  }

  void e() {
    B b;
    AlignedArray result = b.bArray;
  }

  void f() {
    D d;
    AlignedArray result = d.aArray;
  }

  void g() {
    D d;
    AlignedArray result = d.bArray;
  }

  void h(B (*b)[]) {
    AlignedArray result = (*b)->bArray;
  }
}

int incomplete_array_deref(int (*p)[]) { return (*p)[2]; }
