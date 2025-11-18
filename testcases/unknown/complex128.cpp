// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

typedef _Complex float __attribute__((mode(TC))) __complex128;

void check() {
  __complex128 tmp;
}
