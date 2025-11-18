// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);

struct A { 
  A(...) {
    printf("A::A(...)\n"); 
  } 
};

A a(1.34);

A b = 2.34;

int main()
{
  A c[3];
}

