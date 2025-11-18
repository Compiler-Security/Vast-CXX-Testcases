// RUN: %driver -cc1 %isys -x c++ %s %target -o %t%output-suffix && %filecheck


struct Empty;

struct Empty {
  Empty(const Empty &e);
  bool check();
};

bool foo(Empty e) {
  return e.check();
}

void caller(Empty &e) {
  foo(e);
}
