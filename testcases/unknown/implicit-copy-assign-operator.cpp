// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct A { 
  A &operator=(const A&);
  A &operator=(A&);
};

struct B {
  B &operator=(B&);
};

struct C {
  virtual C& operator=(const C&);
};

struct POD {
  int array[3][4];
};

struct CopyByValue {
  CopyByValue(const CopyByValue&);
  CopyByValue &operator=(CopyByValue);
};

struct D : A, B, virtual C { 
  int scalar;
  int scalar_array[2][3];
  B class_member;
  C class_member_array[2][3];
  POD pod_array[2][3];

  union {
    int x;
    float f[3];
  };

  CopyByValue by_value;
};

void test_D(D d1, D d2) {
  d1 = d2;
}

