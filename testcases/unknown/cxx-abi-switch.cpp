// RUN: %driver -cc1 %isys %s -fc++-abi=itanium %target -o %t%output-suffix && %filecheck

class A {
public:
  virtual ~A();
  int x_;
};

class B : public A {
public:
  B(int *i);
  virtual ~B();
  int *i_;
};

B::B(int *i) : i_(i) {}
B::~B() {}

