// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int test1(float F) {
  union {
     float G;
     int i;
  };
  G = F;
  return i;
}

int test2(short F) {
  volatile union {
     short G;
     int i;
  };
  G = F;
  return i;
}

volatile union U_t {
  short S;
  int i;
} U;

int test3(short s) {
  U.S = s;
  return U.i;
}
