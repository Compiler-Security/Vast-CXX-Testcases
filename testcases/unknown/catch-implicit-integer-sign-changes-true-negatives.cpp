// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fsanitize=implicit-integer-sign-change -fno-sanitize-recover=implicit-integer-sign-change %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fsanitize=implicit-integer-sign-change -fsanitize-recover=implicit-integer-sign-change %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fsanitize=implicit-integer-sign-change -fsanitize-trap=implicit-integer-sign-change %s %target -o %t%output-suffix && %filecheck

extern "C" { // Disable name mangling.



__attribute__((no_sanitize("undefined"))) unsigned int ignorelist_0(signed int src) {
  return src;
}

__attribute__((no_sanitize("integer"))) unsigned int ignorelist_1(signed int src) {
  return src;
}

__attribute__((no_sanitize("implicit-conversion"))) unsigned int ignorelist_2(signed int src) {
  return src;
}

__attribute__((no_sanitize("implicit-integer-sign-change"))) unsigned int ignorelist_3(signed int src) {
  return src;
}


unsigned int explicit_signed_int_to_unsigned_int(signed int src) {
  return (unsigned int)src;
}

signed int explicit_unsigned_int_to_signed_int(unsigned int src) {
  return (signed int)src;
}


unsigned int explicit_unsigned_int_to_unsigned_int(unsigned int src) {
  return (unsigned int)src;
}

signed int explicit_signed_int_to_signed_int(signed int src) {
  return (signed int)src;
}


using UnsignedInt = unsigned int;
using SignedInt = signed int;

signed int explicit_functional_unsigned_int_to_signed_int(unsigned int src) {
  return SignedInt(src);
}

unsigned int explicit_functional_signed_int_to_unsigned_int(signed int src) {
  return UnsignedInt(src);
}


unsigned int explicit_functional_unsigned_int_to_unsigned_int(unsigned int src) {
  return UnsignedInt(src);
}

signed int explicit_functional_signed_int_to_signed_int(signed int src) {
  return SignedInt(src);
}


signed int explicit_cppstyle_unsigned_int_to_signed_int(unsigned int src) {
  return static_cast<signed int>(src);
}

unsigned int explicit_cppstyle_signed_int_to_unsigned_int(signed int src) {
  return static_cast<unsigned int>(src);
}


unsigned int explicit_cppstyle_unsigned_int_to_unsigned_int(unsigned int src) {
  return static_cast<unsigned int>(src);
}

signed int explicit_cppstyle_signed_int_to_signed_int(signed int src) {
  return static_cast<signed int>(src);
}

} // extern "C"
