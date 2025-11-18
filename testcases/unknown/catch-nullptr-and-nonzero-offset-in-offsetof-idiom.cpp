// RUN: %driver -cc1 %isys -x c++ %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -x c++ -fsanitize=pointer-overflow -fno-sanitize-recover=pointer-overflow %s %target -o %t%output-suffix && %filecheck

#include <stdint.h>

struct S {
  int x, y;
};

uintptr_t get_offset_of_y_naively() {
  return ((uintptr_t)(&(((S *)nullptr)->y)));
}

uintptr_t get_offset_of_y_via_builtin() {
  return __builtin_offsetof(S, y);
}
