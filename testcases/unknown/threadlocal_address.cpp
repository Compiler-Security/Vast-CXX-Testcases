// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
thread_local int i;
int g() {
  i++;
  return i;
}
int f() {
  thread_local int j = 0;
  j++;
  return j;
}
