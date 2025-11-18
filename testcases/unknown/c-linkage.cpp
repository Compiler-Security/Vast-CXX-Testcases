// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern "C" {
  namespace N {
    struct X { 
      virtual void f();
    };
    void X::f() { }
  }
}


extern "C" {
  static void test2_f() {
  }
  static void test2_f(int x) {
  }
  void test2_use() {
    test2_f();
    test2_f(42);
  }
}

extern "C" {
  struct test3_s {
  };
  bool operator==(const int& a, const test3_s& b)  {
  }
}
