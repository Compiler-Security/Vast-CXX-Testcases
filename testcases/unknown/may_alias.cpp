// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

enum class __attribute__((may_alias)) E {};

template<typename T> struct A {
  using B __attribute__((may_alias)) = enum {};
};

template<typename T> using Alias = typename A<T>::B;

auto foo(E &r) { return r; }

auto goo(A<int>::B &r) { return r; }

auto hoo(Alias<int> &r) { return r; }

