// RUN: %driver -cc1 %isys %s -std=c++11 -finline-functions %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -finline-hint-functions %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fno-inline %target -o %t%output-suffix && %filecheck

struct A {
  A() {}
  A(const A&) {}
  A& operator=(const A&) { return *this; }
  ~A() {}
};

struct B {
  A member;
  int implicitFunction(int a) { return a + a; }
  inline int explicitFunction(int a);
  int noHintFunction(int a);
  __attribute__((optnone)) int optNoneFunction(int a) { return a + a; }
  template<int N> int implicitTplFunction(int a) { return N + a; }
  template<int N> inline int explicitTplFunction(int a) { return N + a; }
  template<int N> int noHintTplFunction(int a);
  template<int N> int explicitRedeclTplFunction(int a);
};

int B::explicitFunction(int a) { return a + a; }
int B::noHintFunction(int a) { return a + a; }

template<> int B::implicitTplFunction<0>(int a) { return a + a; }
template<> int B::explicitTplFunction<0>(int a) { return a + a; }
template<> int B::noHintTplFunction<0>(int a) { return a + a; }
template<> inline int B::implicitTplFunction<1>(int a) { return a; }
template<> inline int B::explicitTplFunction<1>(int a) { return a; }
template<> inline int B::noHintTplFunction<1>(int a) { return a; }
template<int N> int B::noHintTplFunction(int a) { return N + a; }
template<int N> inline int B::explicitRedeclTplFunction(int a) { return N + a; }

constexpr int constexprFunction(int a) { return a + a; }

void foo()
{
  B b1;
  B b2(b1);
  b2 = b1;
  b1.implicitFunction(1);
  b1.explicitFunction(2);
  b1.noHintFunction(3);
  b1.optNoneFunction(4);
  constexprFunction(5);
  b1.implicitTplFunction<0>(6);
  b1.implicitTplFunction<1>(7);
  b1.implicitTplFunction<2>(8);
  b1.explicitTplFunction<0>(9);
  b1.explicitTplFunction<1>(10);
  b1.explicitTplFunction<2>(11);
  b1.noHintTplFunction<0>(12);
  b1.noHintTplFunction<1>(13);
  b1.noHintTplFunction<2>(14);
  b1.explicitRedeclTplFunction<2>(15);
}





