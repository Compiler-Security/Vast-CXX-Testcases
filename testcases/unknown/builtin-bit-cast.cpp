// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck

void test_scalar(int &oper) {
  __builtin_bit_cast(float, oper);

}

struct two_ints {
  int x;
  int y;
};

unsigned long test_aggregate_to_scalar(two_ints &ti) {
  return __builtin_bit_cast(unsigned long, ti);

}

struct two_floats {
  float x;
  float y;
};

two_floats test_aggregate_record(two_ints& ti) {
   return __builtin_bit_cast(two_floats, ti);


}

two_floats test_aggregate_array(int (&ary)[2]) {
  return __builtin_bit_cast(two_floats, ary);


}

two_ints test_scalar_to_aggregate(unsigned long ul) {
  return __builtin_bit_cast(two_ints, ul);

}

unsigned long test_complex(_Complex unsigned &cu) {
  return __builtin_bit_cast(unsigned long, cu);

}

_Complex unsigned test_to_complex(unsigned long &ul) {

  return __builtin_bit_cast(_Complex unsigned, ul);

}

unsigned long test_array(int (&ary)[2]) {
  return __builtin_bit_cast(unsigned long, ary);

}

two_ints test_rvalue_aggregate() {
  return __builtin_bit_cast(two_ints, 42ul);

}
