// RUN: %driver -cc1 %isys -std=c++1z -I%S %s -fcxx-exceptions %target -o %t%output-suffix && %filecheck

#include "typeinfo"

struct A {};

auto &ti_noexcept_ptr = typeid(void (A::*)() noexcept);
auto &ti_noexcept_memptr = typeid(void (A::*)() noexcept);

__attribute__((noreturn)) void f() noexcept {
  throw f;
}

void g(__attribute__((noreturn)) void (A::*p)() noexcept) {
  throw p;
}
