// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int test5(int);
template <typename T>
T test5(T) __attribute__((enable_if(1, "better than non-template")));

int (*Ptr)(int) = &test5;


void test1(int i) __attribute__((enable_if(i == 1, ""))) {}

void ext();
void test2(int i) __attribute__((enable_if(&ext != 0, ""))) {}

void test3(int i, int j) __attribute__((enable_if(i == 1, ""), enable_if(j == 2, ""))) {}

template <typename T>
class test4 {
  virtual void f(int i, int j) __attribute__((enable_if(i == 1, ""))) __attribute__((enable_if(j == 2, "")));
};

template class test4<double>;
