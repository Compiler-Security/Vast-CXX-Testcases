// RUN: %driver -cc1 %isys %s -I%S -std=c++98 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -I%S -std=c++98 -fforce-emit-vtables -fstrict-vtable-pointers -mconstructor-aliases %target -o %t%output-suffix && %filecheck


#include <typeinfo>

namespace Test1 {

struct A {
  A();
  virtual void f();
  virtual ~A() { }
};

A::A() { }

void f(A* a) {
  a->f();
};

void g() {
  A a;
  f(&a);
}

}


namespace Test2 {
  struct A {
    virtual void f();
  };

  const std::type_info &g() {
    return typeid(A);
  };

  void A::f() { }
}

namespace Test3 {

struct A {
  virtual void f();
  virtual ~A() { }
};

struct B : A {
  B();
  virtual void f();
};

B::B() { }

void g(A* a) {
  a->f();
};

}

namespace Test4 {

template <class T> struct RefPtr {
  T* p;
  ~RefPtr() {
    p->deref();
  }
};

struct A {
  virtual ~A();
};

struct Node;

struct B : A {
  virtual void deref();
  RefPtr<Node> m;
};

void f() {
  RefPtr<B> b;
}

}

namespace Test5 {

struct A {
  virtual void f() { }
};

struct B : A { 
  virtual ~B();
};

B::~B() { }

}

namespace Test6 {

struct A {
  virtual ~A();
  int a;
};

struct B {
  virtual ~B();
  int b;
};

struct C : A, B { 
  C();
};

struct D : C {
  virtual void f();
  D();
};

D::D() { }

}

namespace Test7 {

struct c1 {};
struct c10 : c1{
  virtual void foo ();
};
struct c11 : c10, c1{
  virtual void f6 ();
};
struct c28 : virtual c11{
  void f6 ();
};
}

namespace Test8 {
struct X {
  X();
  virtual void foo();
};
struct Y : X {
  void foo();
};

void g(X* p) { p->foo(); }
void f() {
  Y y;
  g(&y);
  X x;
  g(&x);
}

}  // Test8

namespace Test9 {
struct A {
  virtual void foo();
  virtual void bar();
};
void A::bar() {}

struct B : A {
  void foo();
};

void g() {
  A a;
  a.foo();
  B b;
  b.foo();
}

}  // Test9

namespace Test10 {

struct A {
  virtual void foo();
  virtual void bar();
};
void A::foo() {}

struct D : A {
  void bar();
};
inline void D::bar() {}

struct B : A {
  void foo();
  void bar();
};

struct C : A {
  void bar() {}               // defined in body - not key function
  virtual inline void gar();  // inline in body - not key function
  virtual void car();
};


struct E : A {};

void g(A& a) {
  a.foo();
  a.bar();
}

void f() {
  A a;
  g(a);
  B b;
  g(b);
  C c;
  g(c);
  D d;
  g(d);
  E e;
  g(e);
}

}  // Test10

namespace Test11 {
struct D;
struct C {
  virtual D& operator=(const D&);
};

struct D : C {
  virtual void key();
};
D f();

void g(D& a) {
  C c;
  c = a;
  a.key();
  a.key();
}
void g() {
  D d;
  d = f();
  g(d);
}
}  // Test 11

namespace Test12 {

struct A {
  virtual void foo();
  virtual ~A() {}
};
struct B : A {
  void foo();
};

void g() {
  A a;
  a.foo();
  B b;
  b.foo();
}
}

namespace Test13 {


struct A {
  virtual ~A();
};
struct B : A {
  virtual void f();
  void operator delete(void *);
  ~B() {}
};

void g() {
  A *b = new B;
}
}

namespace Test14 {

struct A {
  virtual void f();
  void operator delete(void *);
  ~A();
};

void g() {
  A *b = new A;
  delete b;
}
}

namespace Test15 {
struct A { virtual void f() {} };
struct B : virtual A {};
struct C : virtual A {};
struct D : B, C {
  virtual void g();
  void f();
};

void test() {
  D * d = new D;
  d->f();
}
}

namespace Test16 {

struct S {
  __attribute__((visibility("hidden"))) virtual void doStuff();
};

struct S2 {
  virtual void doStuff();
  __attribute__((visibility("hidden"))) void unused();

};

void test() {
  S *s = new S;
  s->doStuff();

  S2 *s2 = new S2;
  s2->doStuff();
}
}

namespace Test17 {

struct A {
  virtual void key();
  virtual void bar() {}
};

struct B {
  virtual void key();
  virtual ~B() {}
};

void testcaseA() {
  A a;
  a.bar(); // this forces to emit definition of bar
}

void testcaseB() {
  B b; // This only forces emitting of complete object destructor
}

} // namespace Test17

namespace Test18 {

struct Base {
  virtual int fun() { return 42; }
  virtual ~Base() { }
};

struct Derived : Base {
  Derived();
};

int foo() {
  Derived *der = new Derived();
  return der->fun();
}
}

namespace TestTemplates {


template<class T>
struct Template {
  Template();
  virtual T foo(T val);
  virtual T thisShouldBeEmittedToo(T val) { return val; }
  virtual ~Template();
};


struct NonTemplate {
  typedef int T;
  NonTemplate();
  virtual T foo(T val);
  virtual T thisShouldBeEmittedToo(T val) { return val; }
  virtual ~NonTemplate();
};


struct OuterNonTemplate {
  template<class T>
  struct NestedTemplateInNonTemplate {
    NestedTemplateInNonTemplate();
    virtual T foo(T val);
    virtual T thisShouldBeEmittedToo(T val) { return val; }
    virtual ~NestedTemplateInNonTemplate();
  };

  struct NestedNonTemplateInNonTemplate {
    typedef int T;
    NestedNonTemplateInNonTemplate();
    virtual T foo(T val);
    virtual T thisShouldBeEmittedToo(T val) { return val; }
    virtual ~NestedNonTemplateInNonTemplate();
  };
};

template<class>
struct OuterTemplate {
  template<class T>
  struct NestedTemplateInTemplate {
    NestedTemplateInTemplate();
    virtual T foo(T val);
    virtual T thisShouldBeEmittedToo(T val) { return val; }
    virtual ~NestedTemplateInTemplate();
  };

  struct NestedNonTemplateInTemplate {
    typedef int T;
    NestedNonTemplateInTemplate();
    virtual T foo(T val);
    virtual T thisShouldBeEmittedToo(T val) { return val; }
    virtual ~NestedNonTemplateInTemplate();
  };
};

template<class T>
int use() {
  T *ptr = new T();
  return ptr->foo(42);
}

void test() {
  use<Template<int> >();
  use<OuterTemplate<long>::NestedTemplateInTemplate<int> >();
  use<OuterNonTemplate::NestedTemplateInNonTemplate<int> >();

  use<NonTemplate>();
  use<OuterTemplate<long>::NestedNonTemplateInTemplate>();
  use<OuterNonTemplate::NestedNonTemplateInNonTemplate>();
}
}
