// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

void foo(int * __restrict myptr1, int * myptr2) {
  myptr1[0] = 0;
  myptr2[0] = 0;
}
