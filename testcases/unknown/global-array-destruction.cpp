// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);

int count;

struct S {
  S() : iS(++count) { printf("S::S(%d)\n", iS); }
  ~S() { printf("S::~S(%d)\n", iS); }
  int iS;
};


S arr[2][1];
S s1;
S arr1[3];
static S sarr[4];

int main () {}
S arr2[2];
static S sarr1[4];
S s2;
S arr3[3];


struct T {
  double d;
  int n;
  ~T();
};
T t[2][3] = { 1.0, 2, 3.0, 4, 5.0, 6, 7.0, 8, 9.0, 10, 11.0, 12 };


static T t2[2][3] = { 1.0, 2, 3.0, 4, 5.0, 6, 7.0, 8, 9.0, 10, 11.0, 12 };


using U = T[2][3];
U &&u = U{ {{1.0, 2}, {3.0, 4}, {5.0, 6}}, {{7.0, 8}, {9.0, 10}, {11.0, 12}} };

