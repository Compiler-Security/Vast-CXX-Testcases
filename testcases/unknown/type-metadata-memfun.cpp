// RUN: %driver -cc1 %isys -flto -flto-unit -fvisibility=hidden %s %target -o %t%output-suffix && %filecheck

struct S1 {
  S1();
  ~S1();
  virtual void vf();
  void f();
  void fdecl();
};

struct [[clang::lto_visibility_public]] S2 {
  void f();
};


S1::S1() {}
S1::~S1() {}
void S1::vf() {}
void S1::f() {
  fdecl();
}

void S2::f() {}


