// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s -DWIN_TEST %target -o %t%output-suffix && %filecheck

int __regcall foo(int i);

int main()
{
  int p = 0, _data;
  auto lambda = [&](int parameter) -> int {
    _data = foo(parameter);
    return _data;
  };
  return lambda(p);
}

int __regcall foo (int i){
  return i;
}

static int x = 0;
class test_class {
  int a;
public:
#ifndef WIN_TEST
  __regcall
#endif
    test_class(){++x;}

#ifndef WIN_TEST
  __regcall
#endif
  ~test_class(){--x;}

  test_class& __regcall operator+=(const test_class&){
    return *this;
  }
  void __regcall do_thing(){}

  template<typename T>
  void __regcall tempFunc(T i){}
};

bool __regcall operator ==(const test_class&, const test_class&){ --x; return false;}

test_class __regcall operator""_test_class (unsigned long long) { ++x; return test_class{};}

template<typename T>
void __regcall freeTempFunc(T i){}

void force_gen() {
  test_class t;
  test_class t2 = 12_test_class;
  t += t2;
  auto t3 = 100_test_class;
  t3.tempFunc(1);
  freeTempFunc(1);
  t3.do_thing();
}

long double _Complex __regcall foo(long double _Complex f) {
  return f;
}

float _Complex __regcall callee(float _Complex f);

__regcall int
some_really_long_name_that_manages_to_hit_the_right_spot_of_mem(int a) {
  float _Complex x[2];
  x[0] = callee(x[0]);
  return a;
}
