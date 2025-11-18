// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct A {
  A(int);
};

struct B {
  B(A);
};

int main () {
  (B)10;
  B(10);
  static_cast<B>(10);
}

