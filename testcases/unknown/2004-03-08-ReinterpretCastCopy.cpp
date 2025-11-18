// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-rtti %s %target -o %t%output-suffix && %filecheck

struct A {
  virtual void Method() = 0;
};

struct B : public A {
  virtual void Method() { }
};

typedef void (A::*fn_type_a)(void);
typedef void (B::*fn_type_b)(void);

int main(int argc, char **argv)
{
  fn_type_a f = reinterpret_cast<fn_type_a>(&B::Method);
  fn_type_b g = reinterpret_cast<fn_type_b>(f);
  B b;
  (b.*g)();
  return 0;
}
