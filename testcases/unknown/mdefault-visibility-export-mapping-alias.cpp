// RUN: %driver -cc1 %isys %s -mdefault-visibility-export-mapping=none -mconstructor-aliases %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -mdefault-visibility-export-mapping=explicit -mconstructor-aliases %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -mdefault-visibility-export-mapping=all -mconstructor-aliases %target -o %t%output-suffix && %filecheck

class A {
public:
  ~A();
};

A::~A() {}

class __attribute__((visibility("default"))) B {
public:
  ~B();
};

B::~B() {}

void func() {
  A x;
  B y;
}




