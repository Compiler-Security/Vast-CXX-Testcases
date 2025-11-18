// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

int gi;

namespace lambdas {
void Lambdas(char *ptr) {
  auto L1 = [](void *const p __attribute__((pass_object_size(0)))) {
    return __builtin_object_size(p, 0);
  };

  int i = 0;
  auto L2 = [&i](void *const p __attribute__((pass_object_size(0)))) {
    return __builtin_object_size(p, 0) + i;
  };

  gi = L1(ptr);
  gi = L2(ptr);
}

}

namespace addrof {
void OvlFoo(void *const __attribute__((pass_object_size(0)))) {}
void OvlFoo(int *const) {}

void Test() {
  (OvlFoo)(nullptr);

  (&OvlFoo)(nullptr);
}
}

namespace delegate {
  struct A {
    A(void *const p __attribute__((pass_object_size(0))));
  };
  A::A(void *const p __attribute__((pass_object_size(0)))) {}
}

namespace variadic {

struct AsCtor {
  AsCtor(const char *const c __attribute__((pass_object_size(0))), double a,
         ...) {}
};

struct AsMember {
  void bar(const char *const c __attribute__((pass_object_size(0))), double a,
           ...) {}
  void operator()(const char *const c __attribute__((pass_object_size(0))),
                  double a, ...) {}
};

void test() {
  AsCtor("a", 1.0);
  AsMember{}.bar("a", 1.0);
  AsMember{}("a", 1.0);
}
}
