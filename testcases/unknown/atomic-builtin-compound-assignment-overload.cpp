// RUN: %driver -cc1 %isys -std=gnu++11 %s %target -o %t%output-suffix && %filecheck

_Atomic unsigned an_atomic_uint;

enum { an_enum_value = 1 };

void enum1() {
  an_atomic_uint += an_enum_value;
}

void enum2() {
  an_atomic_uint |= an_enum_value;
}

void enum3(_Atomic unsigned &an_atomic_uint_param) {
  an_atomic_uint_param += an_enum_value;
}

void enum4(_Atomic unsigned &an_atomic_uint_param) {
  an_atomic_uint_param |= an_enum_value;
}

volatile _Atomic unsigned an_volatile_atomic_uint;

void enum5() {
  an_volatile_atomic_uint += an_enum_value;
}

void enum6() {
  an_volatile_atomic_uint |= an_enum_value;
}

void enum7(volatile _Atomic unsigned &an_volatile_atomic_uint_param) {
  an_volatile_atomic_uint_param += an_enum_value;
}

void enum8(volatile _Atomic unsigned &an_volatile_atomic_uint_param) {
  an_volatile_atomic_uint_param |= an_enum_value;
}
