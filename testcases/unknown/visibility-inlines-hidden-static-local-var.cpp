// RUN: %driver -cc1 %isys -fvisibility-inlines-hidden -fvisibility-inlines-hidden-static-local-var %s %target -o %t%output-suffix && %filecheck

#define used __attribute__((used))

used inline void f1() {
  static int f1_var = 0;
}

__attribute__((visibility("default")))
used inline void f2() {
  static int f2_var = 0;
}

struct S {
  used void f3() {
    static int f3_var = 0;
  }

  void f6();
  void f7();
};

used void f4() {
  static int f4_var = 0;
}

__attribute__((visibility("default")))
used void f5() {
  static int f5_var = 0;
}

used void S::f6() {
  static int f6_var = 0;
}

used inline void S::f7() {
  static int f7_var = 0;
}


struct __attribute__((visibility("default"))) S2 {
  used void f8() {
    static int f8_var = 0;
  }
};
