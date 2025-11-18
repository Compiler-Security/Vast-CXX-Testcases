// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern int i;

const int &lvalue_noop_cast() {
  if (i == 0)
    return (const int&)17;
  else if (i == 1)
    return static_cast<const int&>(17);
  return 17;
}

const short &lvalue_integral_cast() {
  if (i == 0)
    return (const short&)17;
  else if (i == 1)
    return static_cast<const short&>(17);
  return 17;
}

const short &lvalue_floating_integral_cast() {
  if (i == 0)
    return (const short&)17.5;
  else if (i == 1)
    return static_cast<const short&>(17.5);
  return 17.5;
}

const float &lvalue_integral_floating_cast() {
  if (i == 0)
    return (const float&)17;
  else if (i == 1)
    return static_cast<const float&>(17);
  return 17;
}

const float &lvalue_floating_cast() {
  if (i == 0)
    return (const float&)17.0;
  else if (i == 1)
    return static_cast<const float&>(17.0);
  return 17.0;
}

int get_int();

const bool &lvalue_integer_bool_cast() {
  if (i == 0)
    return (const bool&)get_int();
  else if (i == 1)
    return static_cast<const bool&>(get_int());
  return get_int();
}

float get_float();

const bool &lvalue_floating_bool_cast() {
  if (i == 0)
    return (const bool&)get_float();
  else if (i == 1)
    return static_cast<const bool&>(get_float());
  return get_float();
}

struct X { };
typedef int X::*pm;
typedef int (X::*pmf)(int);

pm get_pointer_to_member_data();
pmf get_pointer_to_member_function();

const bool &lvalue_ptrmem_to_bool_cast() {
  if (i == 0)
    return (const bool&)get_pointer_to_member_data();
  else if (i == 1)
    return static_cast<const bool&>(get_pointer_to_member_data());
  return get_pointer_to_member_data();
}

const bool &lvalue_ptrmem_to_bool_cast2() {
  if (i == 0)
    return (const bool&)get_pointer_to_member_function();
  else if (i == 1)
    return static_cast<const bool&>(get_pointer_to_member_function());
  return get_pointer_to_member_function();
}

_Complex double get_complex_double();

const _Complex float &f1() {
  if (i == 0)
    return (const _Complex float&)get_complex_double();
  else if (i == 1)
    return static_cast<const _Complex float&>(get_complex_double());
  return get_complex_double();
}

unsigned pr10592(const int &v) {
  return static_cast<const unsigned &>(v);
}

namespace PR10650 {
  struct Helper {
    unsigned long long id();
  };
  unsigned long long test(Helper *obj) {
    return static_cast<const unsigned long long&>(obj->id());
  }
}

