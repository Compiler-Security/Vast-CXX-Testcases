// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


# 1 "./template.h" 1
template <typename T>
class Foo {
public:
  int bar();
};
# 21 "./template.hpp"
template <typename T>
int Foo<T>::bar() {
  return 23;
}
int main (int argc, const char * argv[])
{
  Foo<int> f;
  return f.bar();
}
