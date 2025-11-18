// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

typedef char vec_t __attribute__ ((__ext_vector_type__ (8)));
void h() {
  vec_t v(0);
}
