// RUN: %driver -cc1 %isys -std=c++11 -fvisibility-inlines-hidden %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -fvisibility=hidden -fvisibility-inlines-hidden %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -fvisibility=protected -fvisibility-inlines-hidden %s %target -o %t%output-suffix && %filecheck






int func(void) {
  static int var = 0;
  return var++;
}
inline int inline_func(void) {
  static int var = 0;
  return var++;
}
int __attribute__((visibility("hidden"))) hidden_func(void) {
  static int var = 0;
  return var++;
}
inline int __attribute__((visibility("hidden"))) inline_hidden_func(void) {
  static int var = 0;
  return var++;
}
int __attribute__((visibility("default"))) default_func(void) {
  static int var = 0;
  return var++;
}
inline int __attribute__((visibility("default"))) inline_default_func(void) {
  static int var = 0;
  return var++;
}
struct __attribute__((visibility("default"))) ExportedClass {
  int inl_method() {
    static int var = 0;
    return var++;
  }
  int ext_method();
};
int ExportedClass::ext_method() { return inl_method(); }
void bar(void) {
  func();
  inline_func();
  hidden_func();
  inline_hidden_func();
  default_func();
  inline_default_func();
}
