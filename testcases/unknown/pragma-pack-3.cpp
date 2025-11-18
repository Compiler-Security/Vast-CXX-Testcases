// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Base {
  char a;
};

struct Derived_1 : virtual Base
{
  char b;
};

#pragma pack(1)
struct Derived_2 : Derived_1 {
};

Derived_2 x;
