// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  A(const char *);
};


struct S {
  int n;
  A s;
} arr[] = {
  { 0, "hello" },
  { 1, "world" },
  { 2, "goodbye" }
};

