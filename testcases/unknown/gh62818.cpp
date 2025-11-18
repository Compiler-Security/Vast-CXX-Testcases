// RUN: %driver -cc1 %isys -std=c++17 %s %target -o %t%output-suffix && %filecheck

void doSomething();

struct A {
  A() {};
  ~A() noexcept {
    doSomething();
  }

  A & operator=(A a) & noexcept {
    return *this;
  }
};

template<typename T>
struct B {
  void test() {a = {};}

  A a;
};

void client(B<int> &f) {f.test();}
