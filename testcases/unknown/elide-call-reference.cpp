// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A { A(const A&); ~A(); };
A& a();
void b() {
  A x = a();
}

