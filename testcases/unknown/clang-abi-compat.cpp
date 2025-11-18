// RUN: %driver -cc1 %isys -std=c++98 -fenable-matrix -fclang-abi-compat=3.0 %s -Wno-c++11-extensions %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 -fenable-matrix -fclang-abi-compat=3.0 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 -fenable-matrix -fclang-abi-compat=3.8 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 -fenable-matrix -fclang-abi-compat=3.9 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 -fenable-matrix -fclang-abi-compat=4.0 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 -fenable-matrix -fclang-abi-compat=5 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 -fenable-matrix -fclang-abi-compat=11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++20 -fenable-matrix -fclang-abi-compat=11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++20 -fenable-matrix -fclang-abi-compat=12 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++20 -fenable-matrix -fclang-abi-compat=14 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++98 -fenable-matrix -fclang-abi-compat=latest %s -Wno-c++11-extensions %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++20 -fenable-matrix -fclang-abi-compat=latest %s %target -o %t%output-suffix && %filecheck

typedef __attribute__((vector_size(8))) long long v1xi64;
void clang39(v1xi64) {}

struct A {
  A(const A&) = default;
  A(A&&);
};
void clang5(A) {}

namespace mangle_template_prefix {
  template<typename T> void f(typename T::template U<int>::template V<int>, typename T::template U<int>::template V<float>);
  struct T { template<typename I> struct U { template<typename J> using V = int; }; };
  void g() { f<T>(1, 2); }
}

int arg;
template<const int *> struct clang12_unchanged {};
void test(clang12_unchanged<&arg>) {}

#if __cplusplus >= 201703L
template<auto> struct clang12_changed {};
void test(clang12_changed<(const int*)&arg>) {}
#endif

template<const int *> void clang12_a() {}
template void clang12_a<&arg>();

extern const char arr[6] = "hello";
template<const char *> void clang12_b() {}
template void clang12_b<arr>();

template<const char (*)[6]> void clang12_c() {}
template void clang12_c<&arr>();


namespace expr_primary {
struct A {
  template<int N> struct Int {};
  template<int& N> struct Ref {};
};


template <typename T> void test1(typename T::template Int<1> a) {}
template void test1<A>(typename A::template Int<1> a);

enum Enum { EnumVal = 4 };
int Global;

template <typename T> void test2(typename T::template Int<EnumVal> a) {}
template void test2<A>(typename A::template Int<4> a);

template <int X> void test3(typename A::template Int<X> a) {}
template void test3<3>(A::Int<3> a);

#if __cplusplus >= 202002L
template <typename T> void test4(typename T::template Ref<(Global)> a) {}
template void test4<A>(typename A::template Ref<Global> a);

struct B {
  struct X {
    constexpr X(double) {}
    constexpr X(int&) {}
  };
  template<X> struct Y {};
};

template<typename T> void test5(typename T::template Y<1.0>) { }
template void test5<B>(typename B::Y<1.0>);

template<typename T> auto test6(int b) -> typename T::template Y<b> { return {}; }
template auto test6<B>(int b) -> B::Y<b>;
#endif


template <class T> void test7(typename T::template Int<sizeof(char)> a) {}
template void test7<A>(A::Int<1>);

// template<int N> using matrix1xN = int __attribute__((matrix_type(1, N)));
// template<int N> void test8(matrix1xN<N> a) {}
// template void test8<2>(matrix1xN<2> a);

void test9(void) __attribute__((enable_if(1, ""))) {}

}

#if __cplusplus >= 202002L
template <typename T, typename U, typename V, typename W, typename = T, typename = U>
int observe_lambdas(T, U, V, W) { return 0; }
inline auto inline_var_lambda = observe_lambdas([]{}, []{}, (int*)0, (int*)0);
int use_inline_var_lambda() { return inline_var_lambda; }
#endif

struct X {
  struct Y {
    using a = int;
    using b = int;
  };
};
template <typename T> void test10(typename T::Y::a, typename T::Y::b, float*, float*) {}
template void test10<X>(int, int, float*, float*);
