// RUN: %driver -cc1 %isys -I%S %s -fcxx-exceptions -fexceptions -std=c++11 %target -o %t%output-suffix && %filecheck
struct Offset { virtual ~Offset(); };
struct A { virtual ~A(); };
struct B final : Offset, A { };

struct C { virtual ~C(); int c; };
struct D : A { int d; };
struct E : A { int e; };
struct F : virtual A { int f; };
struct G : virtual A { int g; };
struct H final : C, D, E, F, G { int h; };

C *inexact(A *a) {
  return dynamic_cast<C*>(a);
}

B *exact_single(A *a) {



  return dynamic_cast<B*>(a);
}

B &exact_ref(A &a) {



  return dynamic_cast<B&>(a);
}

H *exact_multi(A *a) {



  return dynamic_cast<H*>(a);
}

namespace GH64088 {
  struct A { virtual ~A(); };
  struct B final : A { virtual ~B() = default; };
  B *cast(A *p) { return dynamic_cast<B*>(p); }
}
