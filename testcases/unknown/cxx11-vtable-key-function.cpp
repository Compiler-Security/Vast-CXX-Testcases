// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

namespace Test1 {
struct X {
  virtual ~X(); // Key function.
  virtual void f(); // Not a key function.
};

X::~X() = default;

}

namespace Test2 {
struct X {
  virtual ~X() = default; // Not a key function.
  virtual void f(); // Key function.
};

void X::f() {}

}

namespace Test3 {
struct X {
  virtual ~X() = delete; // Not a key function.
  virtual void f(); // Key function.
};

void X::f() {}

}
