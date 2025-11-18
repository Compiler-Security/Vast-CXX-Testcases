// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

#pragma GCC visibility push(hidden)
struct x {
  static int y;
};
#pragma GCC visibility pop
int x::y = 10;

#pragma GCC visibility push(hidden)
struct __attribute((visibility("default"))) x2 {
  static int y;
};
int x2::y = 10;
#pragma GCC visibility pop

#pragma GCC visibility push(hidden)
template<class T> struct x4 {
  static int y;
};
#pragma GCC visibility pop
template<> int x4<int>::y = 10;

#pragma GCC visibility push(hidden)
template<int x> int f() { return x; }
extern "C" int g() { return f<3>(); }
#pragma GCC visibility pop

#pragma GCC visibility push(hidden)
template<class T> struct x5 {
  void y();
};
#pragma GCC visibility pop
template<> void x5<int>::y() {}

#pragma GCC visibility push(hidden)
namespace n __attribute((visibility("default"))) {
  void f() {}
}
#pragma GCC visibility pop

namespace n __attribute((visibility("default")))  {
#pragma GCC visibility push(hidden)
  void g() {}
#pragma GCC visibility pop
}

namespace test2 {
#pragma GCC visibility push(default)
#pragma GCC visibility push(hidden)
  struct foo { // foo is hidden
  };
#pragma GCC visibility pop
  struct foo; // declaration is ok, we ignore the default in the stack
  template<typename T>
  struct bar { // bar is default
    static void f(){}
  };
#pragma GCC visibility pop
  void zed() {
    bar<foo>::f();
    bar<int>::f();
  }
}
