// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace rdar8818236 {
struct S {
  char c2;
  union {
    char c;
    int i;
  };
};

char S::*foo  = &S::c;
}

struct A {
  union {
    int a;
    void* b;
  };
  
  A() : a(0) { }
};

A a;

namespace PR7021 {
  struct X
  {
    union { long l; };
  };

  void f(X x, X z) {
    X x1;

    x1.l = 1;

    X x2(x1);

    X x3;
    x3 = x1;

  }
}

namespace test2 {
  struct A {
    struct {
      union {
        int b;
      };
    };

    A();
  };

  A::A() : b(10) { }
}

namespace PR10512 {
  struct A {
    A();
    A(int);
    A(long);

    struct {
      struct {int x;};
      struct {int y;};
    };
  };

  A::A() {}

  A::A(int x) : x(x) { }

  A::A(long y) : y(y) { }
}

namespace test3 {
  struct A {
    union {
      mutable char fibers[100];
      struct {
        void (*callback)(void*);
        void *callback_value;
      };
    };

    A();
  };

  A::A() : callback(0), callback_value(0) {}
}

struct S {
  S() : x(42), y(55) {}
  union {
    struct {
      int x;
      union { int y; };
    };
  };
} s;


template <typename T> struct Foo {
  Foo() : ptr(__nullptr) {}
  union {
    T *ptr;
  };
};
Foo<int> f;

namespace PR9683 {
  struct QueueEntry {
    union {
      struct {
        void* mPtr;
        union {
          unsigned mSubmissionTag;
        };
      };
      unsigned mValue;
    };
    QueueEntry() {}
  };
  QueueEntry QE;
}

namespace PR13154 {
  struct IndirectReferenceField {
      struct {
          float &x;
      };
      IndirectReferenceField(float &x);
  };
  IndirectReferenceField::IndirectReferenceField(float &xx) : x(xx) {}
}
