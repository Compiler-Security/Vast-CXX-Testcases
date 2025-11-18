// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++1z %s %target -o %t%output-suffix && %filecheck

struct A {
  static const int Foo = 123;
};
const int *p = &A::Foo; // emit available_externally
const int A::Foo;       // convert to full definition

struct PODWithInit {
  int g = 42;
  char h = 43;
};
struct CreatePOD {
  static constexpr PODWithInit pod{};
};
const int *p_pod = &CreatePOD::pod.g;

struct Bar {
  int b;
};

struct MutableBar {
  mutable int b;
};

struct Foo {
  static constexpr int ConstexprStaticMember = 42;
  static const int ConstStaticMember = 43;

  static constexpr Bar ConstStaticStructMember = {44};

  static constexpr MutableBar ConstexprStaticMutableStructMember = {45};
};
static constexpr int ConstStaticexpr = 46;
static const int ConstExpr = 46;

static constexpr Bar ConstexprStaticStruct = {47};

static constexpr MutableBar ConstexprStaticMutableStruct = {48};

void use(const int &);
void foo() {
  use(Foo::ConstexprStaticMember);
  use(Foo::ConstStaticMember);
  use(Foo::ConstStaticStructMember.b);
  use(Foo::ConstexprStaticMutableStructMember.b);
  use(ConstStaticexpr);
  use(ConstExpr);
  use(ConstexprStaticStruct.b);
  use(ConstexprStaticMutableStruct.b);
}
