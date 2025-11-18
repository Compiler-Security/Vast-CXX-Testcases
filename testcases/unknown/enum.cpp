// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

enum A { a } __attribute((packed));
int func(A x) { return x==a; }
