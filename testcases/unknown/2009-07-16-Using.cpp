// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace A {
  typedef int B;
}
struct B {
};
using ::A::B;
