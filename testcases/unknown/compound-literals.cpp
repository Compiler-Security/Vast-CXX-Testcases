// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct X {
  X();
  X(const X&);
  X(const char*);
  ~X();
};

struct Y { 
  int i;
  X x;
};


int f() {
  return ((Y){17, "seventeen"}).i;
}

int g() {
  const int (&v)[2] = (int [2]) {1,2};

  return v[0];
}


struct Z { int i[3]; };
int *p = (Z){ {1, 2, 3} }.i;

int *q = (int [5]){1, 2, 3, 4, 5};

extern int n;
int *r = (int [5]){1, 2, 3, 4, 5} + n;

int *PR21912_1 = (int []){} + n;

union PR21912Ty {
  long long l;
  double d;
};
union PR21912Ty *PR21912_2 = (union PR21912Ty[]){{.d = 2.0}, {.l = 3}} + n;

int computed_with_lambda = [] {
  int *array = (int[]) { 1, 3, 5, 7 };
  return array[0];
}();
