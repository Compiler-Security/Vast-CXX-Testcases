// RUN: %driver -cc1 %isys -std=c++17 %s %target -o %t%output-suffix && %filecheck

namespace std {
  template<typename T> constexpr T &&move(T &val) { return static_cast<T&&>(val); }
  template<typename T> constexpr T &&move_if_noexcept(T &val);
  template<typename T> constexpr T &&forward(T &val);
  template<typename U, typename T> constexpr T &&forward_like(T &&val);
  template<typename T> constexpr const T &as_const(T &val);

  template<typename T, typename U> T move(U source, U source_end, T dest);
}

class T {};
extern "C" void take(T &&);
extern "C" void take_lval(const T &);

T a;

T &&move_a = std::move(a);
T &&move_if_noexcept_a = std::move_if_noexcept(a);
T &forward_a = std::forward<T&>(a);
T &forward_like_a = std::forward_like<int&>(a);

extern "C" void test(T &t) {
  take(std::move(t));
  take(std::move_if_noexcept(t));
  take(std::forward<T&&>(t));
  take_lval(std::forward_like<int&>(t));
  take_lval(std::as_const<T&&>(t));

  std::move(t, t, t);
}


extern "C" void *use_address() {
  return (void*)&std::move<int>;
}


extern "C" void take_const_int_rref(const int &&);
extern "C" void move_const_int() {
  const int n = 5;
  take_const_int_rref(std::move(n));
}
