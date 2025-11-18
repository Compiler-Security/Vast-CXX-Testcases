// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern void* foo;
static void* const a = foo;
void* bar() { return a; }



