// RUN: %driver -cc1 %isys %s -stack-protector 2 %target -o %t%output-suffix && %filecheck

class A {
 public:
  virtual ~A() {}
};

A g;

