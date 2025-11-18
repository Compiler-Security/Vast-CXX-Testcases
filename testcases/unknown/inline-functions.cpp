// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fms-compatibility %target -o %t%output-suffix && %filecheck

struct A {
    inline void f();
};

void A::f() { }

template<typename> struct B { };

template<> struct B<char> {
  inline void f();
};

void B<char>::f() { }


void f() { }

inline void f1(int);

void f1(int) { }

void test_f1() { f1(17); }

namespace test1 {
  template <typename T> class ClassTemplate {
  private:
    friend void T::func();
    void g() {}
  };


  class C {
  public:
    void func() {
      ClassTemplate<C> ct;
      ct.g();
    }
  };

  void f() {
    C c;
    c.func();
  }
}

namespace test2 {
  struct A;
  void f(const A& a);
  struct A {
    friend void f(const A& a) { } 
  };
  void g() {
    A a;
    f(a);
  }
}

extern inline void ExternAndInlineFn() {}

inline void InlineThenExternFn() {}
extern void InlineThenExternFn();

extern void ExternThenInlineFn() {}

extern void ExternThenInlineThenDefFn();
inline void ExternThenInlineThenDefFn();
void ExternThenInlineThenDefFn() {}

inline void InlineThenExternThenDefFn();
extern void InlineThenExternThenDefFn();
void InlineThenExternThenDefFn() {}

extern constexpr int ExternAndConstexprFn() { return 0; }

constexpr int ConstexprFn() { return 0; }

template <typename T>
extern inline void ExternInlineOnPrimaryTemplate(T);

template <>
void ExternInlineOnPrimaryTemplate(int) {}

template <typename T>
extern inline void ExternInlineOnPrimaryTemplateAndSpecialization(T);

template <>
extern inline void ExternInlineOnPrimaryTemplateAndSpecialization(int) {}

struct TypeWithInlineMethods {
  static void StaticFun() {}
  void NonStaticFun() { StaticFun(); }
};

namespace PR22959 {
template <typename>
struct S;

S<int> Foo();

template <typename>
struct S {
  friend S<int> Foo();
};

__attribute__((used)) inline S<int> Foo() { return S<int>(); }
}
