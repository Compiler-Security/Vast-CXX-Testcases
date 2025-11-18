// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int* a = __null;
int b = __null;

void f() {
  int* c = __null;
  int d = __null;
}
