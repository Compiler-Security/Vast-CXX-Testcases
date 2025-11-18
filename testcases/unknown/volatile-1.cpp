// RUN: %driver -cc1 %isys -Wno-unused-value %s -std=c++98 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -Wno-unused-value %s -std=c++11 %target -o %t%output-suffix && %filecheck

volatile int i, j, k;
volatile int ar[5];
volatile char c;
volatile _Complex int ci;
volatile struct S {
#ifdef __cplusplus
  void operator =(volatile struct S&o) volatile;
#endif
  int i;
} a, b;

int printf(const char *, ...);


void test() {

  asm("nop"); // CHECK: call void asm

  i;

  (float)(ci);

  (void)ci;

  (void)a;

  (void)(ci=ci);

  (void)(i=j);

  ci+=ci;

  (ci += ci) + ci;

  asm("nop"); // CHECK-NEXT: call void asm

  (i += j) + k;

  asm("nop"); // CHECK-NEXT: call void asm

  (i += j) + 1;

  asm("nop"); // CHECK-NEXT: call void asm

  ci+ci;

  __real i;

  +ci;

  asm("nop"); // CHECK-NEXT: call void asm

  (void)(i=i);

  (float)(i=i);

  (void)i; // This is now a load in C++11

  i=i;

  i=i=i;

  (void)__builtin_choose_expr(0, i=i, j=j);

  k ? (i=i) : (j=j);

  (void)(i,(i=i)); // first i is also a load in C++11

  i=i,k; // k is also a load in C++11

  (i=j,k=j);

  (i=j,k); // k is also a load in C++11

  (i,j); // i and j both are loads in C++11

  i=c=k;

  i+=k;

  ci; // ci is a load in C++11

  asm("nop"); // CHECK-NEXT: call void asm

  (int)ci;

  (bool)ci;

  ci=ci;

  asm("nop"); // CHECK-NEXT: call void asm

  ci=ci=ci;

  __imag ci = __imag ci = __imag ci;

  __real (i = j);

  __imag i;
  



  ((a=a),a);

  (void)(a=a);

  __imag (i = j);

  (float)(ci=ci);

  (int)(ci=ci);

  (float)(i=i);

  (int)(i=i);

  -(i=j);

  +(i=k);

  __real (ci=ci);

  i + 0;

  (i=j) + i;

  (i=j) + 0;

  (i,j)=k; // i is also a load in C++11

  (j=k,i)=i;

}
