// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Foo {
  friend bool TryFoo(Foo *f2) { return TryFoo(0, f2); }


  friend bool TryFoo(int, Foo *f3);
};
bool TryFoo(Foo *f5);
int main(void) {
  Foo f;
  TryFoo(&f);
}
