// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

namespace templates {
void *my_malloc(int N) __attribute__((alloc_size(1)));
void *my_calloc(int N, int M) __attribute__((alloc_size(1, 2)));

struct MyType {
  int arr[4];
};

template <typename T> int callMalloc();

template <typename T, int N> int callCalloc();

int testIt() {
  return callMalloc<MyType>() + callCalloc<MyType, 4>();
}

template <typename T> int callMalloc() {
  static_assert(sizeof(T) == 16, "");
  return __builtin_object_size(my_malloc(sizeof(T)), 0);
}

template <typename T, int N> int callCalloc() {
  static_assert(sizeof(T) * N == 64, "");
  return __builtin_object_size(my_malloc(sizeof(T) * N), 0);
}
}

namespace templated_alloc_size {
using size_t = unsigned long;

template <typename T>
T *my_malloc(size_t N = sizeof(T)) __attribute__((alloc_size(1)));

template <typename T>
T *my_calloc(size_t M, size_t N = sizeof(T)) __attribute__((alloc_size(2, 1)));

template <size_t N>
void *dependent_malloc(size_t NT = N) __attribute__((alloc_size(1)));

template <size_t N, size_t M>
void *dependent_calloc(size_t NT = N, size_t MT = M)
    __attribute__((alloc_size(1, 2)));

template <typename T, size_t M>
void *dependent_calloc2(size_t NT = sizeof(T), size_t MT = M)
    __attribute__((alloc_size(1, 2)));

int testIt() {
  return __builtin_object_size(my_malloc<int>(), 0) +
         __builtin_object_size(my_calloc<int>(5), 0) +
         __builtin_object_size(dependent_malloc<6>(), 0) +
         __builtin_object_size(dependent_calloc<7, 8>(), 0) +
         __builtin_object_size(dependent_calloc2<int, 9>(), 0);
}
} // namespace templated_alloc_size

namespace alloc_size_with_cleanups {
struct Foo {
  ~Foo();
};

void *my_malloc(const Foo &, int N) __attribute__((alloc_size(2)));

int testIt() {
  int *const p = (int *)my_malloc(Foo{}, 3);
  return __builtin_object_size(p, 0);
}
} // namespace alloc_size_with_cleanups

class C {
public:
  void *my_malloc(int N) __attribute__((alloc_size(2)));
  void *my_calloc(int N, int M) __attribute__((alloc_size(2, 3)));
};

int callMemberMalloc() {
  return __builtin_object_size(C().my_malloc(16), 0);
}

int callMemberCalloc() {
  return __builtin_object_size(C().my_calloc(16, 2), 0);
}
