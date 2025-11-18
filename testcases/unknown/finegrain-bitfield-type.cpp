// RUN: %driver -cc1 %isys -ffine-grained-bitfield-accesses %s %target -o %t%output-suffix && %filecheck


struct S4 {
  unsigned long f1:28;
  unsigned long f2:4;
  unsigned long f3:12;
};
struct S4 a4;

struct S5 {
  unsigned long f1:28;
  unsigned long f2:4;
  unsigned long f3:28;
  unsigned long f4:4;
  unsigned long f5:12;
};
struct S5 a5;

