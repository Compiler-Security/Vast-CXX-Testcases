// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A;
typedef int A::*param_t;
struct {
  const char *name;
  param_t par;
} ptr;
void test_ptr() { (void) ptr; } // forced use

