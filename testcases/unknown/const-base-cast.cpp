// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A { char x; };
struct B { char y; };
struct C : A,B {};
unsigned char x = ((char*)(B*)(C*)0x1000) - (char*)0x1000;

