// RUN: %driver -cc1 %isys -ftrapv -ftrap-function=mytrap %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrapv %s %target -o %t%output-suffix && %filecheck



void test_builtin(void) {
  __builtin_trap();
}



int test_noreturn(void) {
}



int test_add_overflow(int a, int b) {
  return a + b;
}


