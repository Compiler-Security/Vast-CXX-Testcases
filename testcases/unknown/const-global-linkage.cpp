// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

const int x = 10;
const int y = 20;
const volatile int z = 30;
const int& b() { return y; }

const char z1[] = "asdf";
const char z2[] = "zxcv";
const volatile char z3[] = "zxcv";
const char* b2() { return z2; }
