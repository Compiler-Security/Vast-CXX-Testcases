// RUN: %driver -cc1 %isys -I%S %s -fcxx-exceptions -fexceptions %target -o %t%output-suffix && %filecheck
#include <typeinfo>

namespace Test1 {

struct A { virtual void f(); };

const std::type_info &int_ti = typeid(int);

const std::type_info &A_ti = typeid(const volatile A &);

volatile char c;

const std::type_info &c_ti = typeid(c);

extern const double &d;

const std::type_info &d_ti = typeid(d);

extern A &a;

const std::type_info &a_ti = typeid(a);

const std::type_info &A10_c_ti = typeid(char const[10]);

const char *f() {
  try {
    return typeid(*static_cast<A *>(0)).name();
  } catch (...) {
  }

  return 0;
}

}

