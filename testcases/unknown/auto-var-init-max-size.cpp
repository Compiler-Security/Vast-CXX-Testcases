// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=pattern -ftrivial-auto-var-init-max-size=1 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=pattern -ftrivial-auto-var-init-max-size=1024 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=pattern -ftrivial-auto-var-init-max-size=4096 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=zero -ftrivial-auto-var-init-max-size=1 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=zero -ftrivial-auto-var-init-max-size=1024 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=zero -ftrivial-auto-var-init-max-size=4096 %s %target -o %t%output-suffix && %filecheck

struct Foo {
    int x; // we should try to make sure X is initialized.
    char buff[1024];  // this one is fine to skip
};

int foo(unsigned n) {
  bool var_size_1;
  long var_size_8 = 123;
  void *var_size_8p;
  int var_size_1024[256];
  Foo var_size_1028;
  int var_size_4096[1024];
  int var_vla[n];
  var_size_8p = __builtin_alloca(sizeof(unsigned long long) * n);








  return 0;
}
