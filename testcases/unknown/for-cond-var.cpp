// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  A();
  A(const A &);
  ~A();
  operator bool();
  void *data;
};

A make();
bool cond();
void f(int);

void PR49585() {
  for (
      f(1);

      A a = make();


      f(2)) {
    if (cond()) {
      f(3);
      continue;
    }

    f(4);
  }




}

void PR49585_break() {
  for (
      f(1);

      A a = make();


      f(2)) {
    if (cond()) {
      f(3);
      break;
    }

    f(4);
  }




}

void incless_for_loop() {
  for (; int b = 0;) continue;
}
