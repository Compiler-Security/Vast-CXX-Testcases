// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct Foo {
  int x;
  float y;
  ~Foo() {}
};

struct TestClass {
  int x;

  TestClass() : x(0) {};
  void MemberFunc() {
    Foo f;
    // #pragma clang __debug captured
    // {
    //   static double inner = x;
    //   (void)inner;
    //   f.y = x;
    // }
  }
};

void test1() {
  TestClass c;
  c.MemberFunc();

}


void test2(int x) {
  int y = [&]() {
    // #pragma clang __debug captured
    {
      x++;
    }
    return x;
  }();

}

void test3(int x) {
  // #pragma clang __debug captured
  {
    x = [=]() { return x + 1; } ();
  }
  x = [=]() { return x + 1; }();


}

void test4() {
  // #pragma clang __debug captured
  {
    Foo f;
    f.x = 5;
  }
}

template <typename T, int id>
void touch(const T &) {}

template <typename T, unsigned id>
void template_capture_var() {
  T x;
  // #pragma clang __debug captured
  {
    touch<T, id>(x);
  }
}

template <typename T, int id>
class Val {
  T v;
public:
  void set() {
    // #pragma clang __debug captured
    {
      touch<T, id>(v);
    }
  }

  template <typename U, int id2>
  void foo(U u) {
    // #pragma clang __debug captured
    {
      touch<U, id + id2>(u);
    }
  }
};

void test_capture_var() {
  template_capture_var<int, 201>();

  Val<float, 202> Obj;
  Obj.set();

  Obj.foo<double, 203>(1.0);
}

template <typename T>
void template_capture_lambda() {
  T x, y;
  [=, &y]() {
    // #pragma clang __debug captured
    {
      y += x;
    }
  }();
}

void test_capture_lambda() {
  template_capture_lambda<int>();
}

inline int test_captured_linkage() {
  int j;
  // #pragma clang __debug captured
  // {
  //   static int i = 0;
  //   j = ++i;
  // }
  return j;
}
void call_test_captured_linkage() {
  test_captured_linkage();
}

