// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A { int i; };
struct B { char j; };
struct C : A, B { int k; };

struct D final : virtual C { 
  D(); 
  virtual void f();
};

B &f(D &d) {
  return d;
}
