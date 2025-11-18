// RUN: %driver -cc1 %isys %std_cxx98- %s -I%S -Wno-dynamic-exception-spec %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %std_cxx98- %s -I%S -Wno-dynamic-exception-spec -fvisibility=hidden %target -o %t%output-suffix && %filecheck

#include <typeinfo>





struct A { };

struct B : A {
  virtual void f();
};
void B::f() { }

struct C;

void t1() {
  (void)typeid(C*);
  (void)typeid(C**);
  (void)typeid(int C::*);
  (void)typeid(int C::**);
  (void)typeid(C C::*);
  (void)typeid(C *C::*);
  (void)typeid(C A::*);
  (void)typeid(C* A::*);
}

namespace {
  struct D { };
  
  enum E { };
  
};

struct F {
  virtual void f();
};

inline void F::f() { }
const D getD();

const std::type_info &t2() {
  (void)typeid(const D);
  (void)typeid(D *);
  (void)typeid(D (*)());
  (void)typeid(void (*)(D));
  (void)typeid(void (*)(D&));
  (void)typeid(void (*)() throw (D));
  
  (void)typeid(E);
  
  return typeid(getD());  
}

namespace Arrays {
  struct A {
    static const int a[10];
  };
  const std::type_info &f() {
    return typeid(A::a);
  }
}

template <unsigned N> class T {
  virtual void anchor() {}
};
template class T<1>;
template <> class T<2> { virtual void anchor(); };
void t3() {
  (void) typeid(T<0>);
  (void) typeid(T<1>);
  (void) typeid(T<2>);
}

struct T4 {};
void t4(const T4 *ptr) {
  const void *value = &typeid(ptr);
}

void t5() {
  struct A {};
  const void *value = &typeid(A);
}

inline void t6() {
  struct A {};
  const void *value = &typeid(A);
}
void t6_helper() {
  t6();
}

inline void t7() {
  struct A {};
  const void *value = &typeid(A*);
}
void t7_helper() {
  t7();
}
