// RUN: %driver -cc1 %isys %s -fno-rtti %target -o %t%output-suffix && %filecheck

struct A {
  virtual ~A(){};
};

struct B : public A {
  B() : A() {}
};

A *upcast(B *b) {
  return dynamic_cast<A *>(b);
}

B *samecast(B *b) {
  return dynamic_cast<B *>(b);
}
