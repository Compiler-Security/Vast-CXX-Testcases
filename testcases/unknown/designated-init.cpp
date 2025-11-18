// RUN: %driver -cc1 %isys -std=c++98 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct A { int x, y[3]; };
struct B { A a; };

B b = {(A){1, 2, 3, 4}, .a.y[1] = 5};

union U {
  int n;
  float f;
};
struct C {
  int x;
  U u[3];
};
struct D {
  C c;
};

D d1 = {(C){1, {{.n=2}, {.f=3}, {.n=4}}}, .c.u[1].n = 5};

D d2 = {(C){1, 2, 3, 4}, .c.u[1].f = 5};

struct Bitfield {
  int a : 3;
  int b : 4;
  int c : 5;
};
struct WithBitfield {
  int n;
  Bitfield b;
};
WithBitfield bitfield = {1, (Bitfield){2, 3, 4}, .b.b = 5};

struct String {
  const char buffer[12];
};
struct WithString {
  String str;
};
WithString string = {(String){"hello world"}, .str.buffer[0] = 'H', .str.buffer[6] = 'W'};

struct LargeArray {
  int arr[4096];
};
struct WithLargeArray {
  LargeArray arr;
};
WithLargeArray large = {(LargeArray){1, 2, 3}, .arr.arr[10] = 10};

union OverwritePaddingWithBitfield {
  struct Padding { unsigned : 8; char c; } padding;
  char bitfield : 3;
};
struct WithOverwritePaddingWithBitfield {
  OverwritePaddingWithBitfield a;
};
WithOverwritePaddingWithBitfield overwrite_padding = {(OverwritePaddingWithBitfield){1}, .a.bitfield = 3};
