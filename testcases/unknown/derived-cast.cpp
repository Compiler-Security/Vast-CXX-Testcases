// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

class A {
    int a;
};

class B {
    int b;
public:
    A *getAsA();
};

class X : public A, public B {
    int x;
};


A *B::getAsA() {
  return static_cast<X*>(this);

}

