// RUN: %driver -cc1 %isys -std=c++11 -fmerge-all-constants %s %target -o %t%output-suffix && %filecheck

const char (&extended_string_ref)[5] = {"hi"};

const char (&nonextended_string_ref)[3] = {"hi"};

namespace reference {
  struct A {
    int i1, i2;
  };

  void single_init() {

    const int &cri2a = 1;

    const int &cri1a = {1};

    int i = 1;
    int &ri1a = {i};

    A a{1, 2};
    A &ra1a = {a};

    using T = A&;
    A &ra1b = T{a};

  }

  void reference_to_aggregate(int i) {
    const A &ra1{1, i};

    const int (&arrayRef)[] = {1, 2, i};

    const A &constra1{1, 2};

    const int (&constarrayRef)[] = {1, 2, 3};

  }

  struct B {
    B();
    ~B();
  };

  void single_init_temp_cleanup()
  {

    const B &rb{ B() };
  }

}

namespace PR23165 {
struct AbstractClass {
  virtual void foo() const = 0;
};

struct ChildClass : public AbstractClass {
  virtual void foo() const {}
};

void helper(const AbstractClass &param) {
  param.foo();
}

void foo() {
  helper(ChildClass());
}

struct S { struct T { int a; } t; mutable int b; };
void f() {
  const S::T &r = S().t;
}
}
