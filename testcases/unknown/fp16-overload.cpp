// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern int foo(float x);
extern int foo(double x);

__fp16 a;

int bar (void) { return foo(a); }
