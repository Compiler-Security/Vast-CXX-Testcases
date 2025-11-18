// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace PR5248 {
struct A {
  void copyFrom(const A &src);
  void addRef(void);

  A& operator=(int);
};

void A::copyFrom(const A &src) {
  ((A &)src).addRef();
}
}

void test(PR5248::A* a) {
  reinterpret_cast<PR5248::A&>(*a) = 17;
}
