// RUN: %driver -cc1 %isys -std=c++11 %s -disable-llvm-optzns -fno-unroll-loops %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s -disable-llvm-optzns %target -o %t%output-suffix && %filecheck


void while_test(int *List, int Length) {
  int i = 0;

  while (i < Length) {
    List[i] = i * 2;
    i++;
  }
}

void do_test(int *List, int Length) {
  int i = 0;

  do {
    List[i] = i * 2;
    i++;
  } while (i < Length);
}

void for_test(int *List, int Length) {
  for (int i = 0; i < Length; i++) {
    List[i] = i * 2;
  }
}

