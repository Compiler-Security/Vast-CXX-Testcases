// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Foo {
  Foo();
  Foo(const Foo&);
};

struct Bar {
  Bar();
  operator const Foo&() const;
};

void f(Foo);

void g(Foo foo) {
  f(Bar());
  f(Foo());
  f(foo);
}

