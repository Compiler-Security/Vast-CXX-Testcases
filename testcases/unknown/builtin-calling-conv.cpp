// RUN: %driver -cc1 %isys -DREDECL %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

#ifdef REDECL
namespace std {
#ifdef SPIR
using size_t = unsigned int;
#else
using size_t = unsigned long;
#endif // SPIR
} // namespace std

float __builtin_atan2f(float, float);
void *operator new(std::size_t);
#endif // REDECL

void foo();

void user() {
  int i;
  ::operator new(5);
  (void)__builtin_atan2f(1.1, 2.2);
  foo();
}



