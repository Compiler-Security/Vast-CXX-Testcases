// RUN: %driver -cc1 %isys -fmerge-all-constants %s %target -o %t%output-suffix && %filecheck

struct A {
};

struct B {
  const struct A& a = {};
};

void Test(const struct B&);

void Run() {
  Test({});
}
