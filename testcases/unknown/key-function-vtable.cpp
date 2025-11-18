// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct testa { virtual void a(); };
void testa::a() {}

struct testb { virtual void a() {} };
testb *testbvar = new testb;

struct testc { virtual void a(); };
inline void testc::a() {}

struct testd { inline virtual void a(); };
void testd::a() {}

struct teste { inline virtual void a(); };
teste *testevar = new teste;

namespace {
  struct testf { virtual void a(); };
}
void testf::a() {}

namespace {
  struct testg { virtual void a(); };
}
void testg::a() {}
testg *testgvar = new testg;

struct X0 { virtual ~X0(); };
struct X1 : X0 {
  virtual void f();
};

inline void X1::f() { }

void use_X1() { X1 x1; }

