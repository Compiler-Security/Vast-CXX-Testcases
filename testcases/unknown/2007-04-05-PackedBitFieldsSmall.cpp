// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


#ifdef PACKED
#define P __attribute__((packed))
#else
#define P
#endif

struct P M_Packed {
  unsigned long long X:50;
  unsigned Y:2;
};

struct M_Packed sM_Packed;

int testM_Packed (void) {
  struct M_Packed x;
  return (0 != x.Y);
}

int testM_Packed2 (void) {
  struct M_Packed x;
  return (0 != x.X);
}
