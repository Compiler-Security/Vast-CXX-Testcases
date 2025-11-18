// RUN: %driver -cc1 %isys -std=c++1z %s %target -o %t%output-suffix && %filecheck

struct S { S(); ~S(); };

S global;

inline S inline_global;

thread_local S thread_local_global;

thread_local inline S thread_local_inline_global;

struct A {
  static S member;
  static thread_local S thread_local_member;

  static inline S inline_member;

  static thread_local inline S thread_local_inline_member;
};

void f() {
  static S static_local;

  static thread_local S static_thread_local;
}

S A::member;

thread_local S A::thread_local_member;

template <typename T> struct B {
  static S member;

  static inline S inline_member;

  static thread_local S thread_local_member;

  static thread_local inline S thread_local_inline_member;
};
template<typename T> S B<T>::member;
template<typename T> thread_local S B<T>::thread_local_member;

template<typename ...T> void use(T &...);
void use_b() {
  use(B<int>::member, B<int>::inline_member, B<int>::thread_local_member,
      B<int>::thread_local_inline_member);
}


