// RUN: %driver -cc1 %isys -std=c++1z -fblocks %s %target -o %t%output-suffix && %filecheck

extern "C" int sink;
extern "C" const volatile void* volatile ptr_sink = nullptr;

struct Tag1 {};
struct Tag2 {};
struct Tag3 {};
struct Tag4 {};

constexpr int get_line_constexpr(int l = __builtin_LINE()) {
  return l;
}

int get_line_nonconstexpr(int l = __builtin_LINE()) {
  return l;
}


int get_line(int l = __builtin_LINE()) {
  return l;
}

int get_line2(int l = get_line()) { return l; }


int global_one = __builtin_LINE();
int global_two = get_line_constexpr();
const int global_three(get_line_constexpr());

int global_four = get_line_nonconstexpr();

struct InClassInit {
  int Init = __builtin_LINE();
  int Init2 = get_line2();
  InClassInit();
  constexpr InClassInit(Tag1, int l = __builtin_LINE()) : Init(l), Init2(l) {}
  constexpr InClassInit(Tag2) : Init(__builtin_LINE()), Init2(__builtin_LINE()) {}
  InClassInit(Tag3, int l = __builtin_LINE());
  InClassInit(Tag4, int l = get_line2());

  static void test_class();
};
void InClassInit::test_class() {
  InClassInit test_one;
  InClassInit test_two{Tag1{}};
  InClassInit test_three{Tag2{}};
  InClassInit test_four(Tag3{});
  InClassInit test_five(Tag4{});

}
InClassInit::InClassInit() = default;

InClassInit::InClassInit(Tag3, int l) : Init(l) {}

InClassInit::InClassInit(Tag4, int arg) : Init(arg) {}

void get_line_test() {
  sink = get_line();
  sink = __builtin_LINE();
  ptr_sink = &global_three;
}

void foo() {
  const int N[] = {__builtin_LINE(), get_line_constexpr()};
}
