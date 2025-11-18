// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++03 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

namespace {
  struct A {
    virtual void f() { }
  };
}

void f() { A b; }

struct B {
  B();
  virtual void f();
};

B::B() { }

struct C : virtual B {
  C();
  virtual void f() { }
};

C::C() { }

struct D {
  virtual void f();
};

void D::f() { }

static struct : D { } e;

void use_e() {
  e.f();
}

template<typename T>
struct E {
  virtual ~E();
};

template<typename T> E<T>::~E() { }

template<>
struct E<char> {
  virtual void anchor();
};

void E<char>::anchor() { }

template struct E<short>;
extern template struct E<int>;

void use_E() {
  E<int> ei;
  (void)ei;
  E<long> el;
  (void)el;
}

template<typename T>
struct F {
  virtual void foo() { }
};

template<>
struct F<char> {
  virtual void foo() { }
};

template struct F<short>;
extern template struct F<int>;

void use_F() {
  F<char> fc;
  fc.foo();
  F<int> fi;
  fi.foo();
  F<long> fl;
  (void)fl;
}














template <typename T>
class G {
public:
  G() {}
  virtual void f0();
  virtual void f1();
};
template <>
void G<int>::f1() {}
template <typename T>
void G<T>::f0() {}
void G_f0()  { new G<int>(); }

template <typename T>
class H {
public:
  virtual ~H();
};

void use_H() {
  H<int> h;
}


struct VBase1 { virtual void f(); }; struct VBase2 : virtual VBase1 {};
template<typename T>
struct I : VBase2 {};
extern template struct I<int>;
I<int> i;
