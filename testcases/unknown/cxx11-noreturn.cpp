// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

int g();

[[noreturn]] int f() {
  while (g()) {}
}

