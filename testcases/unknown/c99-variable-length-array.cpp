// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct X {
  X();
  ~X();
};

struct Y {
  Y();
  ~Y();
};

void f(int argc, const char* argv[]) {
  X x;
  const char *argv2[argc];
  Y y;
  for (int i = 0; i != argc; ++i)
    argv2[i] = argv[i];

}

namespace PR11744 {
  template<typename T> int f(int n) {
    T arr[3][n];
    return 3;
  }
  int test = f<int>(0);
}
