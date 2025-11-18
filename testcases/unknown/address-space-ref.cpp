// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fno-delete-null-pointer-checks %target -o %t%output-suffix && %filecheck


typedef int a __attribute__((address_space(1)));

a & foo(a &x, a & y) {
  return x;
}



class bc;
typedef bc b __attribute__((address_space(1)));

b & bar(b &x, b & y) {
  return x;
}



bc & bar2(bc &x, bc & y) {
  return x;
}



