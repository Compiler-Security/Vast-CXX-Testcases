// RUN: %driver -cc1 %isys %s -I%S %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -I%S -fvisibility=hidden %target -o %t%output-suffix && %filecheck

#include <typeinfo>

std::type_info foo() {
  return typeid(void);
}

namespace __cxxabiv1 {
  struct __fundamental_type_info {
    virtual ~__fundamental_type_info();
  };

  __fundamental_type_info::~__fundamental_type_info() { }
}























