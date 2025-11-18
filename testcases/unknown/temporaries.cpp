// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck


namespace PR16263 {
  const unsigned int n = 1234;
  extern const int &r = (const int&)n;

  extern const int &s = reinterpret_cast<const int&>(n);

  struct A { int n; };
  struct B { int n; };
  struct C : A, B {};
  extern const A &&a = (A&&)(A&&)(C&&)(C{});

  extern const int &&t = ((B&&)C{}).n;

  struct D { double d; C c; };
  extern const int &&u = (123, static_cast<B&&>(0, ((D&&)D{}).*&D::c).n);
}

namespace PR20227 {
  struct A { ~A(); };
  struct B { virtual ~B(); };
  struct C : B {};

  A &&a = dynamic_cast<A&&>(A{});

  B &&b = dynamic_cast<C&&>(dynamic_cast<B&&>(C{}));

  B &&c = static_cast<C&&>(static_cast<B&&>(C{}));
}

namespace BraceInit {
  typedef const int &CIR;
  CIR x = CIR{3};
}

namespace RefTempSubobject {
  // struct SelfReferential {
  //   int *p = ints;
  //   int ints[3] = {1, 2, 3};
  // };

  // constexpr const SelfReferential &sr = SelfReferential();
}

struct A {
  A();
  ~A();
  void f();
};

void f1() {
  (void)A();

  A().f();
}

struct B {
  B();
  ~B();
};

B g();

void f2() {
  (void)g();
}

struct C {
  C();
  ~C();

  C f();
};

void f3() {
  C().f();
}

struct D {
  D();
  ~D();

  D operator()();
};

void f4() {
  D()();
}

struct E {
  E();
  ~E();
  E operator+(const E&);
  E operator!();
};

void f5() {
  E() + E();

  !E();
}

struct F {
  F();
  ~F();
  F& f();
};

void f6() {
  F().f();
}

struct G {
  G();
  G(A);
  ~G();
  operator A();
};

void a(const A&);

void f7() {
  a(A());

  a(G());
}

namespace PR5077 {

struct A {
  A();
  ~A();
  int f();
};

void f();
int g(const A&);

struct B {
  int a1;
  int a2;
  B();
  ~B();
};

B::B()
  : a1(A().f())
  , a2(g(A()))
{
  f();
}

}

A f8() {
  return A();
}

struct H {
  H();
  ~H();
  H(const H&);
};

void f9(H h) {
  f9(H());

  f9(h);
}

void f10(const H&);

void f11(H h) {
  f10(H());

  f10(h);
}

struct I {
  I(const char *);
  ~I();
};

I f12() {
  return "Hello";
}

namespace PR5867 {
  struct S {
    S();
    S(const S &);
    ~S();
  };

  void f(S, int);
  void g() {
    (f)(S(), 0);
  }

  template<typename T>
  void g2(T) {
    (f)(S(), 0);
  }

  void h() {
    g2(17);
  }
}

namespace PR6199 {
  struct A { ~A(); };

  struct B { operator A(); };

  template<typename T> A f2(T) {
    B b;
    return b;
  }

  template A f2<int>(int);

}

namespace T12 {

struct A {
  A();
  ~A();
  int f();
};

int& f(int);

void g() {
  int& i = f(A().f());
}

}

namespace PR6648 {
  struct B {
    ~B();
  };
  B foo;
  struct D;
  D& zed(B);
  void foobar() {
    zed(foo);
  }
}

namespace UserConvertToValue {
  struct X {
    X(int);
    X(const X&);
    ~X();
  };

  void f(X);

  void g() {
    f(1);
  }
}

namespace PR7556 {
  struct A { ~A(); };
  struct B { int i; ~B(); };
  struct C { int C::*pm; ~C(); };
  void foo() {
    A();
    B();
    C();
  }
}

namespace Elision {
  struct A {
    A(); A(const A &); ~A();
    void *p;
    void foo() const;
  };

  void foo();
  A fooA();
  void takeA(A a);

  void test0() {

    A i = (foo(), A());

    A j = (fooA(), A());

    A k = (A(), fooA());

  }


  void test1(bool c, A x) {

    A i = (c ? A() : x);

    A j = (c ? x : A());

  }

  A test2() {
    return (foo(), A());
  }

  A test3(int v, A x) {
    if (v < 5)
      return (v < 0 ? A() : x);
    else
      return (v > 10 ? x : A());

  }

  void test4() {

    A x;

    A xs[] = { A(), x };


  }

  struct B { A a; B(); };
  A test5() {

    takeA(B().a);

    A x = B().a;

    return B().a;

  }

  struct C { operator A() const; };
  void test6(const C *x) {
    A(*x).foo();
  }
}

namespace PR8623 {
  struct A { A(int); ~A(); };

  void foo(bool b) {
    b ? A(2) : A(3);
  }
}

namespace PR11365 {
  struct A { A(); ~A(); };

  void foo() {

    (void) (A [3]) {};
  }
}

namespace AssignmentOp {
  struct A { ~A(); };
  struct B { A operator=(const B&); };
  struct C : B { B b1, b2; };
  void f(C &c1, const C &c2) {
    c1 = c2;
  }

}

namespace BindToSubobject {
  struct A {
    A();
    ~A();
    int a;
  };

  void f(), g();

  int &&a = A().a;

  int &&b = (f(), A().a);

  int A::*h();

  int &&c = (f(), (g(), A().*h()));

  struct B {
    int padding;
    A a;
  };

  int &&d = (B().a).*h();
}

namespace Bitfield {
  struct S { int a : 5; ~S(); };

  int &&r = S().a;
}

// namespace Vector {
//   typedef __attribute__((vector_size(16))) int vi4a;
//   typedef __attribute__((ext_vector_type(4))) int vi4b;
//   struct S {
//     vi4a v;
//     vi4b w;
//   };
//   int &&r = S().v[1];

//   int &&s = S().w[1];
// }

namespace ImplicitTemporaryCleanup {
  struct A { A(int); ~A(); };
  void g();

  void f() {
    A &&a = 0;

    g();

  }
}

namespace MultipleExtension {
  struct A { A(); ~A(); };
  struct B { B(); ~B(); };
  struct C { C(); ~C(); };
  struct D { D(); ~D(); int n; C c; };
  struct E { const A &a; B b; const C &c; ~E(); };

  E &&e1 = { A(), B(), D().c };




  E e2 = { A(), B(), D().c };





  void g();
  void f() {
    E &&e1 = { A(), B(), D().c };

    g();

    E e2 = { A(), B(), D().c };

    g();

  }
}

namespace ArrayAccess {
  struct A { A(int); ~A(); };
  void g();
  void f() {
    using T = A[3];

    A &&a = T{1, 2, 3}[1];

    A &&b = 2[T{4, 5, 6}];

    g();

  }
}

namespace PR14130 {
  struct S { S(int); };
  struct U { S &&s; };
  U v { { 0 } };
}

namespace Conditional {
  struct A {};
  struct B : A { B(); ~B(); };
  struct C : A { C(); ~C(); };

  void g();

  void f(bool b) {
    A &&r = b ? static_cast<A&&>(B()) : static_cast<A&&>(C());

    g();


  }

  struct D { A &&a; };
  void f_indirect(bool b) {
    D d = b ? D{B()} : D{C()};





    g();
  }

  extern bool b;
  A &&r = b ? static_cast<A&&>(B()) : static_cast<A&&>(C());
}

#if __cplusplus >= 201703L
namespace PR42220 {
  struct X { X(); ~X(); };
  struct A { X &&x; };
  struct B : A {};
  void g() noexcept;
  void f() {
    B &&b = {X()};
    g();
  }
}
#endif
