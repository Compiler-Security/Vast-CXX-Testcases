// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

struct A {
  unsigned x : 1;
  unsigned   : 1;

  friend bool operator==(A, A);
};


struct B {
  unsigned x : 1;
  unsigned   : 31;

  friend bool operator==(B, B);
};

bool operator==(A, A) = default;


bool operator==(B, B) = default;

