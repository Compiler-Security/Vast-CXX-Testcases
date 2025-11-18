// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

enum MyEnum : char;
void bar(MyEnum value) { }

void foo(MyEnum value)
{
  bar(value);
}
