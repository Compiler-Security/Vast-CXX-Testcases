// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern const int a,b;
const int a=b,b=a;
int c() { if (a) return 1; return 0; }
