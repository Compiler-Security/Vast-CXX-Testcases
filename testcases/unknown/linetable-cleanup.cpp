// RUN: %driver -cc1 %isys -gno-column-info %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -gno-column-info -std=c++98 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -gno-column-info -std=c++11 %s %target -o %t%output-suffix && %filecheck





class C {
public:
  ~C() {}
  int i;
};

int foo()
{
  C c;
  c.i = 42;
  return 0;
}

void bar()
{
  if (!foo())
    return;

  if (foo()) {
    C c;
    c.i = foo();
  }
}

void baz()
{
  if (!foo())
    return;

  if (foo()) {
    return;
  }
}
