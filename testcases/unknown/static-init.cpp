// RUN: %driver -cc1 %isys %s -std=c++98 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++20 %target -o %t%output-suffix && %filecheck





struct A {
  A();
  ~A();
};

void f() {
  static A a;
}

void g() {
  static A& a = *new A;
}

int a();
void h() {
  static const int i = a();
}

inline void h2() {
  static int i = a();
}

void h3() {
  h2();
}

namespace test0 {
  struct A { A(); };
  __attribute__((noreturn)) int throw_exception();

  void test() {
    throw_exception();
    static A r;
  }
}

namespace test1 {
  static inline int getvar(int index) {
    static const int var[] = { 1, 0, 2, 4 };
    return var[index];
  }

  void test() { (void) getvar(2); }
}

char base_req[] = { "foo" };
unsigned char base_req_uchar[] = { "bar" };

namespace union_static_local {
  union x { long double y; const char *x[2]; };
  void f(union x*);
  void test() {
    static union x foo = { .x = { "a", "b" } };
    struct c {
      static void main() {
        f(&foo);
      }
    };
    c::main();
  }
}

namespace test2 {
  struct A {
    A();
    ~A();
  };

  struct B : virtual A {
    B();
    ~B();
  };

  extern int foo();
  B::B() {
    static int x = foo();
  }


  B::~B() {
    static int y = foo();
  }

}

namespace test3 {
  struct A {
    A();
    ~A();
  };

  struct B : virtual A {
    B();
    ~B();
  };

  B::B() {
    union U { char x; int i; };
    static U u = { 'a' };
  }
}

namespace test4 {
struct HasVTable {
  virtual void f();
};
inline HasVTable &useStaticLocal() {
  static HasVTable obj;
  return obj;
}
void useit() {
  useStaticLocal();
}
}

#if __cplusplus >= 202002L
namespace test5 {
  struct A {
    constexpr A(int x) : x_(x) {}
    constexpr ~A() {}
    int x_;
  };
  const int *f() {
    static const A a{42};
    return &a.x_;
  }
}
#endif
