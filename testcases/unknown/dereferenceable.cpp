// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A { void *p; void *q; void *r; };

struct B : A {};
static_assert(sizeof(B) == 24);

B &f(B &b) { return b; }

struct C : virtual A {};
static_assert(sizeof(C) == 32);

C &f(C &c) { return c; }
