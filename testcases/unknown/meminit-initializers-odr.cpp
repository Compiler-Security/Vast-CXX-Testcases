// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

struct ThisShouldBeCalled {
    ThisShouldBeCalled() {}
};

template <typename T>
struct ThisShouldBeCalledTPL {
    ThisShouldBeCalledTPL() {}
};

consteval int f () {
    return 42;
}

struct WithConsteval {
    WithConsteval(int x = f()) {}
};

template <typename T>
struct WithConstevalTPL {
    WithConstevalTPL(T x = f()) {}
};


struct Base {
    ThisShouldBeCalled y = {};
};

struct S : Base {
    ThisShouldBeCalledTPL<int> A =  {};
    WithConsteval B = {};
    WithConstevalTPL<double> C = {};
};
// void Do(S = S{}) {}

// void test() {
//     Do();
// }


namespace check_arrays {

template <typename T>
struct inner {
    inner() {}
};

struct S {
   inner<int> a {};
};

class C {
    S s[1]{};
};

int f() {
    C c;
    return 0;
}


}

namespace check_field_inits_in_base_constructors {

template <typename>
struct ShouldBeODRUsed {
  ShouldBeODRUsed() {}
};
class k {
private:
  ShouldBeODRUsed<k> a = {};
};

struct b {
  k c{};
};
void test() { b d; }


}

namespace check_referenced_when_defined_in_default_parameter {

template <typename T>
struct Test {
    Test(auto&&) {}
};

struct Options {
    Test<bool(bool x)> identity = [](bool x) -> bool { return x; };
};

struct Wrapper {
  Wrapper(const Options& options = Options());
};

void Func() { Options options; }


}

namespace lambda_body {
template <typename a>
int templated_func() {
    return 0;
}
struct test_body {
  int mem = templated_func<int>();
};
struct test_capture {
  int mem = templated_func<double>();
};

struct S {
  int a = [_ = test_capture{}] { (void)test_body{}; return 0;}();
};

void test() {
    S s;
}



}
