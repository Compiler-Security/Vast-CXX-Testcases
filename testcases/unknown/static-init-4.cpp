// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

typedef __attribute__((vector_size(4*4))) float float32x4_t;
union QDSUnion { float32x4_t q; float s[4]; };
constexpr float32x4_t a = {1,2,3,4};
QDSUnion t = {{(a)}};
