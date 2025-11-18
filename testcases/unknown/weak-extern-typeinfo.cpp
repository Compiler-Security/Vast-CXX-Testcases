// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

#define WEAK __attribute__ ((weak)) 

class WEAK A {
  virtual void foo();
};

class B : public A {
  virtual void foo();
};
void A::foo() { }
void B::foo() { }

class T {};
class T1 {};

class C : public T1, public B, public T {
  virtual void foo();
};
void C::foo() { }

class V1 : public virtual A {
  virtual void foo();
};

class V2 : public virtual V1 {
  virtual void foo();
};
void V1::foo() { }
void V2::foo() { }

