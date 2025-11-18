// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct A {
  A(const A&);
  A();
  ~A();
}; 

struct B : public A {
  B();
  B(const B& Other);
  ~B();
};

struct C : public B {
  C();
  C(const C& Other);
  ~C();
}; 

struct X {
  operator B&();
  operator C&();
  X(const X&);
  X();
  ~X();
  B b;
  C c;
};

void test0_helper(A);
void test0(X x) {
  test0_helper(x);
}

struct Base;

struct Root {
  operator Base&();
};

struct Derived;

struct Base : Root {
  Base(const Base &);
  Base();
  operator Derived &();
};

struct Derived : Base {
};

void test1_helper(Base);
void test1(Derived bb) {
  test1_helper(bb);
}

class Test2a {};
class Test2b final : public virtual Test2a {};
void test2(Test2b &x) {
  Test2a &y = x;
}
