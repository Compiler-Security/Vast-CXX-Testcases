// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern const int W __attribute__((weak)) = 99;
const int S = 77;

extern const int C1 = S;

extern const int C2 = W;
