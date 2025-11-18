// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix &>> /home/yibozhang/src/mlir/test/debug.log && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -fclang-abi-compat=4.0 %s %target -o %t%output-suffix &>> /home/yibozhang/src/mlir/test/debug.log && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s -fms-compatibility -fms-compatibility-version=18 %target -o %t%output-suffix &>> /home/yibozhang/src/mlir/test/debug.log && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s -fms-compatibility -fms-compatibility-version=19 %target -o %t%output-suffix &>> /home/yibozhang/src/mlir/test/debug.log && %filecheck

namespace trivial {
struct A {
  void *p;
};
void foo(A);
void bar() {
  foo({});
}

}

namespace default_ctor {
struct A {
  A();
  void *p;
};
void foo(A);
void bar() {
  foo({});
}

}

namespace move_ctor {
struct A {
  A();
  A(A &&o);
  void *p;
};
void foo(A);
void bar() {
  foo({});
}

}

namespace all_deleted {
struct A {
  A();
  A(const A &o) = delete;
  A(A &&o) = delete;
  void *p;
};
void foo(A);
void bar() {
  foo({});
}

}

namespace implicitly_deleted {
struct A {
  A();
  A &operator=(A &&o);
  void *p;
};
void foo(A);
void bar() {
  foo({});
}

}

namespace one_deleted {
struct A {
  A();
  A(A &&o) = delete;
  void *p;
};
void foo(A);
void bar() {
  foo({});
}

}

namespace copy_defaulted {
struct A {
  A();
  A(const A &o) = default;
  A(A &&o) = delete;
  void *p;
};
void foo(A);
void bar() {
  foo({});
}

}

namespace move_defaulted {
struct A {
  A();
  A(const A &o) = delete;
  A(A &&o) = default;
  void *p;
};
void foo(A);
void bar() {
  foo({});
}

}

namespace trivial_defaulted {
struct A {
  A();
  A(const A &o) = default;
  void *p;
};
void foo(A);
void bar() {
  foo({});
}

}

namespace two_copy_ctors {
struct A {
  A();
  A(const A &) = default;
  A(const A &, int = 0);
  void *p;
};
struct B : A {};

void foo(B);
void bar() {
  foo({});
}

}

namespace definition_only {
struct A {
  A();
  A(A &&o);
  void *p;
};
void *foo(A a) { return a.p; }
}

namespace deleted_by_member {
struct B {
  B();
  B(B &&o);
  void *p;
};
struct A {
  A();
  B b;
};
void *foo(A a) { return a.b.p; }
}

namespace deleted_by_base {
struct B {
  B();
  B(B &&o);
  void *p;
};
struct A : B {
  A();
};
void *foo(A a) { return a.p; }
}

namespace deleted_by_member_copy {
struct B {
  B();
  B(const B &o) = delete;
  void *p;
};
struct A {
  A();
  B b;
};
void *foo(A a) { return a.b.p; }
}

namespace deleted_by_base_copy {
struct B {
  B();
  B(const B &o) = delete;
  void *p;
};
struct A : B {
  A();
};
void *foo(A a) { return a.p; }
}

namespace explicit_delete {
struct A {
  A();
  A(const A &o) = delete;
  void *p;
};
void *foo(A a) { return a.p; }
}

namespace implicitly_deleted_copy_ctor {
struct A {
  A &operator=(const A&);
  int &&ref;
};
int &foo(A a) { return a.ref; }

struct B {
  B &operator=(const B&);
  int &ref;
};
int &foo(B b) { return b.ref; }

struct X { X(const X&); };
struct Y { Y(const Y&) = default; };

union C {
  C &operator=(const C&);
  X x;
  int n;
};
int foo(C c) { return c.n; }

struct D {
  D &operator=(const D&);
  union {
    X x;
    int n;
  };
};
int foo(D d) { return d.n; }

union E {
  E &operator=(const E&);
  Y y;
  int n;
};
int foo(E e) { return e.n; }

struct F {
  F &operator=(const F&);
  union {
    Y y;
    int n;
  };
};
int foo(F f) { return f.n; }
}
