// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct S { S(); ~S(); S(const S &); void operator()(int); };
using size_t = decltype(sizeof(int));
S operator"" _x(const char *, size_t);
S operator"" _y(wchar_t);
S operator"" _z(unsigned long long);
S operator"" _f(long double);
S operator"" _r(const char *);
template<char...Cs> S operator"" _t() { return S(); }


void f() {
  "foo"_x, "bar"_x, L'a'_y, 42_z, 1.0_f;

  123_r, 4.9_r, 0xffff\
eeee_r;

  0x12345678_t;
}


template<typename T> auto g(T t) -> decltype("foo"_x(t)) { return "foo"_x(t); }
template<typename T> auto i(T t) -> decltype(operator"" _x("foo", 3)(t)) { return operator"" _x("foo", 3)(t); }

void h() {
  g(42);
  i(42);
}



