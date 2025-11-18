// RUN: %driver -cc1 %isys %s -fno-use-cxa-atexit %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys %s -fno-use-cxa-atexit -mconstructor-aliases %target -o %t%output-suffix && %filecheck



class A {
public:
  A();
  ~A();
};

A a, b;





void func() {
  static A a1, a2;
}

