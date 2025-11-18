// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct A { virtual ~A(); };
template<typename T> struct B : virtual A {
  ~B() override {}
};
struct C : B<int>, B<float> { C(); ~C() override; };
struct D : C { ~D() override; };

D *p = new D;
