// RUN: %driver -cc1 %isys -fblocks %s %target -o %t%output-suffix && %filecheck


struct A
{
    ~A();
};
int foo(A);

void bar(A &a)
{
    asm("" : : "r"(foo(a)) );
}

namespace TestTemplate {


template <class T>
void foo0(A &a) {
  asm("" : : "r"(foo(a)) );
  asm("");
}

void test0(A &a) { foo0<void>(a); }



template <class T>
void foo1(A a) {
  // asm("" : : "r"(^{ (void)a; return 0; }()));
  asm("");
}

void test1(A &a) { foo1<void>(a); }
} // namespace TestTemplate
