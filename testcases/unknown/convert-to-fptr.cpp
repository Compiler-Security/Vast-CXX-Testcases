// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);

int f1(int arg)  { return arg; }; 

int f2(float arg) { return int(arg); }; 

typedef int (*fp1)(int); 

typedef int (*fp2)(float); 

struct A {
  operator fp1() { return f1; }
  operator fp2() { return f2; } 
} a;


typedef int (&fr1)(int); 
typedef int (&fr2)(float); 

struct B {
  operator fr1() { return f1; }
  operator fr2() { return f2; } 
} b;

int main()
{
 int i = a(10); // Calls f1 via pointer returned from conversion function
 printf("i = %d\n", i);

 int j = b(20); // Calls f1 via pointer returned from conversion function
 printf("j = %d\n", j);
 return 0;
}

