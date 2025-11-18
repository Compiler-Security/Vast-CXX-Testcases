// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A { operator int(); float y; };
struct B : A { double z; };
void a() { switch(B()) {} }

