// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck


struct A { int x, y[2]; int arr[3]; };
int f(int i) {
  constexpr A a = {1, 2, 3, 4, 5, 6};

  return [] (int n, int A::*p) {
    return (n >= 0
      ? a.arr[n]
      : (n == -1
        ? a.*p
        : a.y[2 - n]));
  }(i, &A::x);
}

namespace PR42276 {
  class State {
    void syncDirtyObjects();
    void f1(), f2();
    using l = void (State::*)();
    static constexpr l m[]{&State::f1, &State::f2};
  };
  void State::syncDirtyObjects() {
    for (int i = 0; i < sizeof(m) / sizeof(m[0]); ++i)
      (this->*m[i])();
  }
}
