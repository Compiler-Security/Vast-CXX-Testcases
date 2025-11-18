// RUN: %driver -cc1 %isys %s -I%S -fstrict-vtable-pointers %target -o %t%output-suffix && %filecheck

struct A {
  virtual ~A();
};
struct B : virtual A {};
class C : B {};
C foo;

