// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

void f(const char*);

void g() {
  f("hello");
}
