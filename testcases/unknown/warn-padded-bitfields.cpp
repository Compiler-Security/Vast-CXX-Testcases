// RUN: %driver -cc1 %isys -Wpadded-bitfield %s %target -o %t%output-suffix && %filecheck

struct S1 {
  unsigned a : 1;
  unsigned long long : 0; // expected-warning {{padding struct 'S1' with 63 bits to align anonymous bit-field}}
};

struct S2 {
  unsigned a : 1;
  unsigned long long b : 64; // expected-warning {{padding struct 'S2' with 63 bits to align 'b'}}
};

struct S3 {
  char a : 1;
  short b : 16; // expected-warning {{padding struct 'S3' with 15 bits to align 'b'}}
};

struct [[gnu::packed]] S4 {
  char a : 1;
  short b : 16;
};

struct S5 {
  unsigned a : 1;
  unsigned long long b : 63;
};

struct S6 {
  unsigned a : 1;
  unsigned long long b;
};

struct S7 {
  int word;
  struct {
    int filler __attribute__ ((aligned (8)));
  };
};

void f(S1, S2, S3, S4, S5, S6, S7){}
