// RUN: %driver -cc1 %isys -std=c++11 %s -fms-extensions -fno-rtti %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -x c -Wno-strict-prototypes %s -fms-extensions -fno-rtti %target -o %t%output-suffix && %filecheck


#ifdef __cplusplus
extern "C"
#endif
int printf(const char *, ...);

void funcNoProto() {
  printf("__FUNCSIG__ %s\n\n", __FUNCSIG__);
}

void funcNoParams(void) {
  printf("__FUNCSIG__ %s\n\n", __FUNCSIG__);
}

void freeFunc(int *p, char c) {
  printf("__FUNCSIG__ %s\n\n", __FUNCSIG__);
}

#ifdef __cplusplus
void funcVarargs(...) {
  printf("__FUNCSIG__ %s\n\n", __FUNCSIG__);
}

struct TopLevelClass {
  void topLevelMethod(int *, char);
};
void TopLevelClass::topLevelMethod(int *, char) {
  printf("__FUNCSIG__ %s\n\n", __FUNCSIG__);
}

namespace NS {
struct NamespacedClass {
  void namespacedMethod(int *, char);
};
void NamespacedClass::namespacedMethod(int *, char) {
  printf("__FUNCSIG__ %s\n\n", __FUNCSIG__);
}
}
#endif
