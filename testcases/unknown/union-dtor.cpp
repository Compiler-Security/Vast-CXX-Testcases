// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck


template<bool b = false>
struct Foo {
  Foo() { static_assert(b, "Foo::Foo used"); }
  ~Foo() { static_assert(b, "Foo::~Foo used"); }
};

struct Bar {
  Bar();
  ~Bar();
};

union FooBar {
  FooBar() {}
  ~FooBar() {}
  Foo<> foo;
  Bar bar;
};

struct Variant {
  Variant() {}
  ~Variant() {}
  union {
    Foo<> foo;
    Bar bar;
  };
};

FooBar foobar;
Variant variant;

