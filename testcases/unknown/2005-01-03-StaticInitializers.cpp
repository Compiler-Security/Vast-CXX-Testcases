// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct S {
  int  A[2];
};

int XX = (int)(long)&(((struct S*)0)->A[1]);
