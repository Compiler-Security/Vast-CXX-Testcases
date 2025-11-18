// RUN: %driver -cc1 %isys -fms-extensions %s -o- %target -o %t%output-suffix && %filecheck

struct A {
  void foo() __unaligned;
  void foo() const __unaligned;
  void foo() volatile __unaligned;
  void foo() const volatile __unaligned;
};

void A::foo() __unaligned {}

void A::foo() const __unaligned {}

void A::foo() volatile __unaligned {}

void A::foo() const volatile __unaligned {}
