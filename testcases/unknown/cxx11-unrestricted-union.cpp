// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct A {
  A(); A(const A&); A(A&&); A &operator=(const A&); A &operator=(A&&); ~A();
};
struct B {
  B(); B(const B&); B(B&&); B &operator=(const B&); B &operator=(B&&); ~B();
};

union U {
  U();
  U(const U &);
  U(U &&);
  U &operator=(const U&);
  U &operator=(U&&);
  ~U();

  A a;
  int n;
};

U::U() {}
U::U(const U&) {}
U::U(U&&) {}
U &U::operator=(const U&) { return *this; }
U &U::operator=(U &&) { return *this; }
U::~U() {}

struct S {
  S();
  S(const S &);
  S(S &&);
  S &operator=(const S&);
  S &operator=(S&&);
  ~S();

  union {
    A a;
    int n;
  };
  B b;
  int m;
};

S::S() {}


S::S(const S&) {}


S::S(S&&) {}

S &S::operator=(const S&) { return *this; }

S &S::operator=(S &&) { return *this; }

S::~S() {}

