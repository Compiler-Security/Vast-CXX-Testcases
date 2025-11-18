// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Foo {
  unsigned file_id;

  Foo(unsigned arg);
};

Foo::Foo(unsigned arg) : file_id(arg = 42)
{ }

