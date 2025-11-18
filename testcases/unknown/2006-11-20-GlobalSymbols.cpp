// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int foo __asm__("f\001oo");

int bar() {
  return foo;
}
