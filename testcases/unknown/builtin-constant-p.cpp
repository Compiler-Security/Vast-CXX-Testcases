// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

template <typename T>
constexpr bool is_constant(const T v) {
  return __builtin_constant_p(v);
}

template <typename T>
class numeric {
 public:
  using type = T;

  template <typename S>
  constexpr numeric(S value)
      : value_(static_cast<T>(value)) {}

 private:
  const T value_;
};

bool bcp() {
  return is_constant(numeric<int>(1));
}

struct with_dtor {
  ~with_dtor();
};
bool bcp_stmt_expr_1() {
  return __builtin_constant_p(({with_dtor wd; 123;}));
}

int do_not_call();
bool bcp_stmt_expr_2(int n) {
  return __builtin_constant_p(({
    typedef int arr[do_not_call()];
    n;
  }));
}
