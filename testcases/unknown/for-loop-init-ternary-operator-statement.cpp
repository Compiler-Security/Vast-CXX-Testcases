// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int f() {
  for (int i = 0; int x = i < 2 ? 1 : 0; i++) {
    return x;
  }
  return 0;
}

