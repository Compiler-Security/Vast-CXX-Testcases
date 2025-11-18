// RUN: %driver -cc1 %isys -ffine-grained-bitfield-accesses %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ffine-grained-bitfield-accesses -fsanitize=address %s %target -o %t%output-suffix && %filecheck

struct S1 {
  unsigned f1:2;
  unsigned f2:6;
  unsigned f3:8;
  unsigned f4:4;
  unsigned f5:8;
};

S1 a1;
unsigned read8_1() {
  return a1.f3;
}
void write8_1() {
  a1.f3 = 3;
}

unsigned read8_2() {
  return a1.f5;
}
void write8_2() {
  a1.f5 = 3;
}

struct S2 {
  unsigned long f1:16;
  unsigned long f2:16;
  unsigned long f3:6;
};

S2 a2;
unsigned read16_1() {
  return a2.f1;
}
unsigned read16_2() {
  return a2.f2;
}

void write16_1() {
  a2.f1 = 5;
}
void write16_2() {
  a2.f2 = 5;
}

struct S3 {
  unsigned long f1:14;
  unsigned long f2:18;
  unsigned long f3:32;
};

S3 a3;
unsigned read32_1() {
  return a3.f3;
}
void write32_1() {
  a3.f3 = 5;
}
