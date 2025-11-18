// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct S {
  int field1 : 5;
  int field2 : 6;
  int field3 : 3;
};

void use(bool cond, struct S s1, struct S s2, int val1, int val2) {

  cond ? s1.field1 = val1 : s1.field2 = val2;




  (void)(cond ? s2.field1 = val1 : s2.field2 = val2);




}


void use2(bool cond1, bool cond2, struct S s1, int val1, int val2, int val3) {

  cond1 ? s1.field1 = val1 : cond2 ? s1.field2 = val2 : s1.field3 = val3;





}

