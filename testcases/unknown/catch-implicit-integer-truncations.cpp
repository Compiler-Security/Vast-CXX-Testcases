// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fsanitize=implicit-unsigned-integer-truncation,implicit-signed-integer-truncation -fno-sanitize-recover=implicit-unsigned-integer-truncation,implicit-signed-integer-truncation %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fsanitize=implicit-unsigned-integer-truncation,implicit-signed-integer-truncation -fsanitize-recover=implicit-unsigned-integer-truncation,implicit-signed-integer-truncation %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fsanitize=implicit-unsigned-integer-truncation,implicit-signed-integer-truncation -fsanitize-trap=implicit-unsigned-integer-truncation,implicit-signed-integer-truncation %s %target -o %t%output-suffix && %filecheck

extern "C" { // Disable name mangling.


unsigned char explicit_cast_interference0(unsigned int c) {
  return (unsigned short)c;
}

unsigned char explicit_cast_interference1(unsigned int c) {
  unsigned short b;
  return (unsigned char)(b = c);
}



unsigned char explicit_unsigned_int_to_unsigned_char(unsigned int src) {
  return (unsigned char)src;
}

unsigned char explicit_signed_int_to_unsigned_char(signed int src) {
  return (unsigned char)src;
}

signed char explicit_unsigned_int_to_signed_char(unsigned int src) {
  return (signed char)src;
}

signed char explicit_signed_int_to_signed_char(signed int src) {
  return (signed char)src;
}


unsigned int explicit_unsigned_int_to_unsigned_int(unsigned int src) {
  return (unsigned int)src;
}

signed int explicit_signed_int_to_signed_int(signed int src) {
  return (signed int)src;
}

unsigned char explicit_unsigned_char_to_signed_char(unsigned char src) {
  return (unsigned char)src;
}

signed char explicit_signed_char_to_signed_char(signed char src) {
  return (signed char)src;
}


using UnsignedChar = unsigned char;
using SignedChar = signed char;
using UnsignedInt = unsigned int;
using SignedInt = signed int;

unsigned char explicit_functional_unsigned_int_to_unsigned_char(unsigned int src) {
  return UnsignedChar(src);
}

unsigned char explicit_functional_signed_int_to_unsigned_char(signed int src) {
  return UnsignedChar(src);
}

signed char explicit_functional_unsigned_int_to_signed_char(unsigned int src) {
  return SignedChar(src);
}

signed char explicit_functional_signed_int_to_signed_char(signed int src) {
  return SignedChar(src);
}


unsigned int explicit_functional_unsigned_int_to_unsigned_int(unsigned int src) {
  return UnsignedInt(src);
}

signed int explicit_functional_signed_int_to_signed_int(signed int src) {
  return SignedInt(src);
}

unsigned char explicit_functional_unsigned_char_to_signed_char(unsigned char src) {
  return UnsignedChar(src);
}

signed char explicit_functional_signed_char_to_signed_char(signed char src) {
  return SignedChar(src);
}


unsigned char explicit_cppstyleunsigned_int_to_unsigned_char(unsigned int src) {
  return static_cast<unsigned char>(src);
}

unsigned char explicit_cppstylesigned_int_to_unsigned_char(signed int src) {
  return static_cast<unsigned char>(src);
}

signed char explicit_cppstyleunsigned_int_to_signed_char(unsigned int src) {
  return static_cast<signed char>(src);
}

signed char explicit_cppstylesigned_int_to_signed_char(signed int src) {
  return static_cast<signed char>(src);
}


unsigned int explicit_cppstyleunsigned_int_to_unsigned_int(unsigned int src) {
  return static_cast<unsigned int>(src);
}

signed int explicit_cppstylesigned_int_to_signed_int(signed int src) {
  return static_cast<signed int>(src);
}

unsigned char explicit_cppstyleunsigned_char_to_signed_char(unsigned char src) {
  return static_cast<unsigned char>(src);
}

signed char explicit_cppstylesigned_char_to_signed_char(signed char src) {
  return static_cast<signed char>(src);
}

} // extern "C"

template <typename a>
a b(a c, const a &d) {
  if (d)
    ;
  return c;
}

extern "C" { // Disable name mangling.

int false_positive_with_MaterializeTemporaryExpr() {
  int e = b<unsigned>(4, static_cast<unsigned>(4294967296));
  return e;
}


} // extern "C"
