// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct X {
  ~X();
};

void foo() {
  X v;

TryAgain:
  goto TryAgain;
}
