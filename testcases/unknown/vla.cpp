// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

template<typename T>
struct S {
  static int n;
};
template<typename T> int S<T>::n = 5;

int f() {
  int a[S<int>::n];
  return sizeof a;
}

void test0(void *array, int n) {

  typedef short array_t[n][n+1];

  array_t &ref = *(array_t*) array;

  ref[1][2] = 3;

  short s = ref[4][5];

}


void test2(int b) {
  int varr[b];

  
  b = 15;
  
  
  
  for (int d : varr) 0;
}

void test3(int b, int c) {
  int varr[b][c];
  
  
  b = 15;
  c = 15;
  
 
  for (auto &d : varr) 0;
}


