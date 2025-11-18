// RUN: %driver -cc1 %isys -std=c++11 -UDESUGAR %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -DDESUGAR %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -UDESUGAR -DTEMPLATE %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -DDESUGAR -DTEMPLATE %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -UDESUGAR -DTEMPLATE -DDEPENDENT %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -DDESUGAR -DTEMPLATE -DDEPENDENT %s %target -o %t%output-suffix && %filecheck

struct A {
  A();
  A(const A &);
  ~A();
};

struct B {
  B();
  B(const B &);
  ~B();
};

struct C {
  C(const B &);
  C(const C &);
  ~C();
};

struct E;
struct D {
  D(const C &);
  D(const D &);
  ~D();
};
E begin(D);
E end(D);

struct F;
struct G;
struct H;
struct E {
  E(const E &);
  ~E();
  F operator*();
  G operator++();
  H operator!=(const E &o);
};

struct I;
struct F {
  F(const F &);
  ~F();
  operator I();
};

struct G {
  G(const G &);
  ~G();
  operator bool();
};

struct H {
  H(const H &);
  ~H();
  operator bool();
};

struct I {
  I(const I &);
  ~I();
};

void body(const I &);

#ifdef TEMPLATE
#ifdef DEPENDENT
template<typename D>
#else
template<typename>
#endif
#endif
void for_temps() {
  A a;
#ifdef DESUGAR
  {
    auto && __range = D(B());
    for (auto __begin = begin(__range), __end = end(__range);
         __begin != __end; ++__begin) {
      I i = *__begin;
      body(i);
    }
  }
#else
  for (I i : D(B())) {
    body(i);
  }
#endif
}

#ifdef TEMPLATE
template void for_temps<D>();
#endif






