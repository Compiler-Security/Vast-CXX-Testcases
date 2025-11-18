// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Base {
  virtual ~Base();
  int x;
};

#pragma pack(1)
struct Sub : virtual Base {
  char c;
};

Sub f(Sub x) {
  return x;
}

static int i[sizeof(Sub) == 21 ? 1 : -1];
