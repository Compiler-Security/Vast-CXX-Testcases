// RUN: %driver -cc1 %isys -no-enable-noundef-analysis -std=c++11 -fsanitize=signed-integer-overflow,integer-divide-by-zero,float-divide-by-zero,shift-base,shift-exponent,unreachable,return,vla-bound,alignment,null,vptr,object-size,float-cast-overflow,bool,enum,array-bounds,function -fsanitize-recover=signed-integer-overflow,integer-divide-by-zero,float-divide-by-zero,shift-base,shift-exponent,vla-bound,alignment,null,vptr,object-size,float-cast-overflow,bool,enum,array-bounds,function %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -no-enable-noundef-analysis -std=c++11 -fsanitize=vptr,address -fsanitize-recover=vptr,address %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -no-enable-noundef-analysis -std=c++11 -fsanitize=vptr -fsanitize-recover=vptr %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -no-enable-noundef-analysis -std=c++11 -fsanitize=function %s %target -o %t%output-suffix && %filecheck

struct S {
  double d;
  int a, b;
  virtual int f();
};



struct T : S {};

void reference_binding(int *p, S *q) {



  int &r = *p;

  S &r2 = *q;
}

void member_access(S *p) {










  int k = p->b;







  k = p->f();
}

int lsh_overflow(int a, int b) {






  return a << b;
}

int no_return() {
}

bool sour_bool(bool *p) {
  return *p;
}

enum E1 { e1a = 0, e1b = 127 } e1;
enum E2 { e2a = -1, e2b = 64 } e2;
enum E3 { e3a = (1u << 31) - 1 } e3;

int bad_enum_value() {
  int a = e1;

  int b = e2;

  int c = e3;
  return a + b + c;
}

void bad_downcast_pointer(S *p) {





  (void) static_cast<T*>(p);
}

void bad_downcast_reference(S &p) {






  (void) static_cast<T&>(p);
}

int array_index(const int (&a)[4], int n) {
  int k1 = a[n];

  const int *r1 = &a[n];

  int k2 = ((const int(&)[8])a)[n];

  int k3 = n[a];

  return k1 + *r1 + k2;
}

int multi_array_index(int n, int m) {
  int arr[4][6];


  return arr[n][m];
}

int array_arith(const int (&a)[4], int n) {
  const int *k1 = a + n;

  const int *k2 = (const int(&)[8])a + n;

  return *k1 + *k2;
}

struct ArrayMembers {
  int a1[5];
  int a2[1];
};
int struct_array_index(ArrayMembers *p, int n) {
  return p->a1[n];
}

int flex_array_index(ArrayMembers *p, int n) {
  return p->a2[n];
}

extern int incomplete[];
int incomplete_array_index(int n) {
  return incomplete[n];
}

// typedef __attribute__((ext_vector_type(4))) int V4I;
// int vector_index(V4I v, int n) {
//   return v[n];
// }

char string_index(int n) {
  return "Hello"[n];
}

class A // align=4
{
  int a1, a2, a3;
};

class B // align=8
{
  long b1, b2;
};

class C : public A, public B // align=16
{
  alignas(16) int c1;
};


void downcast_pointer(B *b) {
  (void) static_cast<C*>(b);
}

void downcast_reference(B &b) {
  (void) static_cast<C&>(b);
}

void indirect_function_call(void (*p)(int)) {



  p(42);
}

namespace VBaseObjectSize {
  struct alignas(16) A { void *a1, *a2; };
  struct B : virtual A { void *b; void* g(); };
  struct C : virtual A, virtual B { };
  B &f(B &b) {

    return b;
  }

  void *B::g() {
    return nullptr;
  }
}

namespace FunctionSanitizerVirtualCalls {
struct A {
  virtual void f() {}
  virtual void g() {}
  void h() {}
};

struct B : virtual A {
  virtual void b() {}
  virtual void f();
  void g() final {}
  static void q() {}
};

void B::f() {}

void force_irgen() {
  A a;
  a.g();
  a.h();

  B b;
  b.f();
  b.b();
  b.g();
  B::q();
}


}

namespace UpcastPointerTest {
struct S {};
struct T : S { double d; };
struct V : virtual S {};

S* upcast_pointer(T* t) {


  return t;
}

V getV();

void upcast_to_vbase() {


  const S& s = getV();
}
}

struct nothrow {};
void *operator new[](__SIZE_TYPE__, nothrow) noexcept;

namespace NothrowNew {
  struct X { X(); };

  void *nothrow_new_trivial() {

    return new (nothrow{}) char[123456];
  }

  void *nothrow_new_nontrivial() {

    return new (nothrow{}) X[123456];
  }

  void *throwing_new(int size) {
    return new char[size];
  }

  void *nothrow_new_zero_size() {
    return new char[0];
  }

  void *throwing_new_zero_size() {
    return new (nothrow{}) char[0];
  }
}

struct ThisAlign {
  void this_align_lambda();
  void this_align_lambda_2();
};
void ThisAlign::this_align_lambda() {
  [&] { return this; } ();
}

namespace CopyValueRepresentation {

  struct CustomCopy { CustomCopy(); CustomCopy(const CustomCopy&); };
  struct S1 {
    CustomCopy CC;
    bool b;
  };
  void callee1(S1);
  void test1() {
    S1 s11;
    callee1(s11);
    S1 s12;
    s12 = s11;
  }

  static bool some_global_bool;
  struct ExprCopy {
    ExprCopy();
    ExprCopy(const ExprCopy&, bool b = some_global_bool);
  };
  struct S2 {
    ExprCopy EC;
    bool b;
  };
  void callee2(S2);
  void test2(void) {
    S2 s21;
    callee2(s21);
    S2 s22;
    s22 = s21;
  }

  struct CustomAssign { CustomAssign &operator=(const CustomAssign&); };
  struct S3 {
    CustomAssign CA;
    bool b;
  };
  void test3() {
    S3 x, y;
    x = y;
  }

  struct CustomMove {
    CustomMove();
    CustomMove(const CustomMove&&);
    CustomMove &operator=(const CustomMove&&);
  };
  struct S4 {
    CustomMove CM;
    bool b;
  };
  void test4() {
    S4 x, y;
    x = static_cast<S4&&>(y);
  }

  struct EnumCustomCopy {
    EnumCustomCopy();
    EnumCustomCopy(const EnumCustomCopy&);
  };
  struct S5 {
    EnumCustomCopy ECC;
    bool b;
  };
  void callee5(S5);
  void test5() {
    S5 s51;
    callee5(s51);
    S5 s52;
    s52 = s51;
  }
}

void ThisAlign::this_align_lambda_2() {
  auto *p = +[] {};
  p();
}


