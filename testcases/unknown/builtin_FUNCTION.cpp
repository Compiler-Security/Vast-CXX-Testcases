// RUN: %driver -cc1 %isys -std=c++2a -fblocks %s %target -o %t%output-suffix && %filecheck

namespace test_func {

constexpr const char *test_default_arg(const char *f = __builtin_FUNCTION()) {
  return f;
}

const char *global = test_default_arg();

const char *global_two = __builtin_FUNCTION();

const char * const global_three = test_default_arg();


const char *test_func_one() {
  return __builtin_FUNCTION();
}

const char *test_func_two() {
  return __builtin_FUNCTION();
}

void do_default_arg_test() {
  test_default_arg();
}

} // namespace test_func
