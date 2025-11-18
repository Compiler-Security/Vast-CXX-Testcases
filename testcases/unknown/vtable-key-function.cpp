// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
namespace PR5697 {
struct A {
  virtual void f() { } 
  A();
  A(int);
};

A::A() { }
A::A(int) { }
}

template<typename T>
struct Base {
  virtual ~Base();
};

template<typename T>
struct Derived : public Base<T> { };

template<>
struct Derived<char> : public Base<char> {
  virtual void anchor();
};

void Derived<char>::anchor() { }
