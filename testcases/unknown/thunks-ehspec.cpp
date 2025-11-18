// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions %s -funwind-tables=2 %target -o %t%output-suffix && %filecheck


struct A {
  virtual void primary_key();
};
struct B {
  virtual void secondary();
  virtual void secondary_vararg(int, ...);
};
class C : A, B {
  virtual void primary_key();
  void secondary() noexcept;
  void secondary_vararg(int, ...) noexcept;
};
void C::primary_key() {}


