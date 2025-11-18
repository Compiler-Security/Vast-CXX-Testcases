// RUN: %driver -cc1 %isys -flto -flto-unit -fvirtual-function-elimination -fwhole-program-vtables %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -flto -flto-unit -fwhole-program-vtables %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -flto=thin -flto-unit -fwhole-program-vtables %s %target -o %t%output-suffix && %filecheck


namespace {
struct A {
  A() {}
  virtual int f() { return 1; }
};
}
void *construct_A() {
  return new A();
}


struct __attribute__((visibility("hidden"))) B {
  B() {}
  virtual int f() { return 1; }
};
B *construct_B() {
  return new B();
}


struct __attribute__((visibility("default"))) C {
  C() {}
  virtual int f() { return 1; }
};
C *construct_C() {
  return new C();
}


struct __attribute__((visibility("hidden"))) [[clang::lto_visibility_public]] D {
  D() {}
  virtual int f() { return 1; }
};
D *construct_D() {
  return new D();
}


struct __attribute__((visibility("hidden"))) E : C {
  E() {}
  virtual int f() { return 1; }
};
E *construct_E() {
  return new E();
}


namespace {
struct __attribute__((visibility("hidden"))) F : C {
  F() {}
  virtual int f() { return 1; }
};
}
void *construct_F() {
  return new F();
}


namespace {
struct __attribute__((visibility("hidden"))) G : B {
  G() {}
  virtual int f() { return 1; }
};
}
void *construct_G() {
  return new G();
}


