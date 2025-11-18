// RUN: %driver -cc1 %isys -mrelocation-model static %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -mrelocation-model static -fno-plt %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck




struct C {
  C();
  virtual void foo() {}
};
C::C() {}

struct HasVTable {
  virtual void f();
};
inline HasVTable &useStaticLocal() {
  static HasVTable obj;
  return obj;
}
void useit() {
  useStaticLocal();
}

namespace guard {
int f();
inline int g() {
  static int a = f();
  return a;
}
int h() {
  return g();
}
} // namespace guard


namespace test2 {
void foo();
template <typename T>
struct bar {
  virtual void zed();
  static const int x = 42;
  bar() { foo(); }
};
extern template class bar<char>;
bar<char> abc;
const int *getX() {
  return &bar<int>::x;
}
} // namespace test2
