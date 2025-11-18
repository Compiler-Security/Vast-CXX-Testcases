// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

__attribute__((section("A")))
const int a = 1;
const int *f() { return &a; }

int init();
__attribute__((section("B")))
const int b = init();

__attribute__((section("C")))
int c = 2;

__attribute__((section("D")))
int d = init();

__attribute__((section("E")))
int e;
