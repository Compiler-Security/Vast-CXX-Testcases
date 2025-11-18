// RUN: %driver -cc1 %isys -std=c++11 -fsanitize=signed-integer-overflow,integer-divide-by-zero,float-divide-by-zero,shift-base,shift-exponent,unreachable,return,vla-bound,alignment,null,vptr,object-size,float-cast-overflow,bool,enum,array-bounds,function %s %target -o %t%output-suffix && %filecheck

bool GetOptionalBool(bool *value);
bool GetBool(bool default_value) {
  bool value;
  return GetOptionalBool(&value) ? value : default_value;
}
