// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int test(int i) {
  (void)__datasizeof(int[i++]);
  return i;
}
