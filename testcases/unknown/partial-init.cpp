// RUN: %driver -cc1 %isys -std=c++11 -fcxx-exceptions -fexceptions %s %target -o %t%output-suffix && %filecheck

namespace std {
  struct string {
    const char *p;
    string(const char *s);
    ~string();
  };
}

struct Bar {
  int a;
};

struct Foo {
  std::string c;
  Bar d[32];
};

static Foo table[] = {
  { "blerg" },
};

