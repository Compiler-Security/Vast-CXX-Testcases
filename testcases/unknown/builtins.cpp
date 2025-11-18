// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern "C" {
namespace X {
double __builtin_fabs(double);
float __builtin_fabsf(float) noexcept;
} // namespace X
}

int o = X::__builtin_fabs(-2.0);

long p = X::__builtin_fabsf(-3.0f);

extern "C" char memmove();

int main() {
  return memmove();
}

struct S;
S *addressof(bool b, S &s, S &t) {
  return __builtin_addressof(b ? s : t);
}

namespace std { template<typename T> T *addressof(T &); }

S *std_addressof(bool b, S &s, S &t) {
  return std::addressof(b ? s : t);
}

namespace std { template<typename T> T *__addressof(T &); }

S *std___addressof(bool b, S &s, S &t) {
  return std::__addressof(b ? s : t);
}

extern "C" int __builtin_abs(int); // #1
long __builtin_abs(long);          // #2
extern "C" int __builtin_abs(int); // #3

int x = __builtin_abs(-2);

long y = __builtin_abs(-2l);

extern const char char_memchr_arg[32];
char *memchr_result = __builtin_char_memchr(char_memchr_arg, 123, 32);

int constexpr_overflow_result() {
  constexpr int x = 1;
  constexpr int y = 2;
  int z;

  __builtin_sadd_overflow(x, y, &z);
  return z;
}
