// RUN: %driver -cc1 %isys -std=c++98 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 %s %target -o %t%output-suffix && %filecheck

struct A {
  virtual ~A();
};

struct B : A { };

struct C {
  int i;
  B b;
};

void test_value_init() {

  C c = { 17 } ;
}

enum enum_type { negative_number = -1, magic_number = 42 };

class enum_holder
{
  enum_type m_enum;

public:
  enum_holder() : m_enum(magic_number) { }
};

struct enum_holder_and_int
{
  enum_holder e;
  int i;
};

void test_enum_holder_and_int() {
  enum_holder_and_int();
}

namespace test1 {
  struct A {
    int A::*f;
    A();
    A(const A&);
    A &operator=(const A &);
  };

  struct B {
    A base;
  };

  void foo() {
    B();
  }
}

namespace ptrmem {
  struct S {
    int mem1;
    int S::*mem2;
  };

  int test(S *s) {
    return s->*S().mem2;
  }
}

namespace PR9801 {

struct Test {
  Test() : i(10) {}
  Test(int i) : i(i) {}
  int i;
private:
  int j;
};

struct Test2 {
  Test t;
};

struct Test3 : public Test { };

void f() {
  Test partial[3] = { 1 };

  Test empty[3] = {};

  Test2 empty2[3] = {};

  Test3 empty3[3] = {};
}

}

namespace zeroinit {
  struct S { int i; };

  int test() {
    return S().i;
  }

  struct X0 {
    X0() { }
    int x;
  };

  struct X1 : X0 {
    int x1;
    void f();
  };

  void testX0_X1() {
    X1().f();
  }

  template<typename>
  struct X2 : X0 {
    int x2;
    void f();
  };

  template<typename>
  struct X3 : X2<int> { 
    X3() : X2<int>() { }
    int i;
  };
  

  void testX0_X3() {
    X3<int>().f();
  }

}

namespace PR8726 {
class C;
struct S {
  const C &c1;
  int i;
  const C &c2;
};
void f(const C& c) {
  S s = {c, 42, c};
}

}

namespace test6 {
  struct A { A(); A(int); };

  void test() {
    A arr[10][20] = { 5 };
  };




}

namespace PR11124 {
  struct A { int a; A(); A(int); };
  struct B : virtual A { int b; };
  struct C : B { C(); };      
  C::C() : A(3), B() {}

  struct B2 : virtual A { int B::*b; };
  struct C2 : B2 { C2(); };      
  C2::C2() : A(3), B2() {}
}

void r170806_a(bool b = bool());
void r170806_b() { r170806_a(); }

namespace PR20256 {
  struct data { int i; };

  template<typename T = int>
  data g() {
    data d; // not value-init
    return d;
  }
  template data g();

  template<typename ...T>
  data h(T ...t) {
    data d(t...); // value-init
    return d;
  }
  template data h();


  template<typename T = int>
  data j() {
    data d = {}; // value-init
    return d;
  }
  template data j();

  data f() {
    data d; // not value-init
    return d;
  }

  data i() {
    data d = {}; // value-init
    return d;
  }
}

int explicitly_defaulted() {
  struct A { A() = default; int n; };
  A a = A();
  return a.n;
} // CHECK-LABEL: }


#if __cplusplus >= 201103L
namespace transparent_init_list {
  struct optional_assign_base {};
  struct optional_data_dtor_base { char dummy_[24]; };
  struct optional : optional_data_dtor_base, optional_assign_base {};
  optional f(optional a) { return {optional(a)}; }
}
#endif
