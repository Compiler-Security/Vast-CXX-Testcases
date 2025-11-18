// RUN: %driver -cc1 %isys %s -internal-isystem %S -mdefault-visibility-export-mapping=none %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -internal-isystem %S -mdefault-visibility-export-mapping=explicit %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -internal-isystem %S -mdefault-visibility-export-mapping=explicit -DFUNDAMENTAL_IS_EXPLICIT %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -internal-isystem %S -mdefault-visibility-export-mapping=all %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -internal-isystem %S -mdefault-visibility-export-mapping=all -fvisibility=hidden %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -internal-isystem %S -mdefault-visibility-export-mapping=all -DFUNDAMENTAL_IS_EXPLICIT -fvisibility=hidden %target -o %t%output-suffix && %filecheck

#include <typeinfo>

struct C;

struct __attribute__((type_visibility("default"))) D;

void __attribute__((visibility("default"))) tfunc() {
  (void)typeid(C *);
  (void)typeid(C **);
  (void)typeid(D *);
  (void)typeid(D **);
}

struct s {
  virtual void foo();
};
void s::foo() {}

struct __attribute__((type_visibility("default"))) t {
  virtual void foo();
};
void t::foo() {}

#ifdef FUNDAMENTAL_IS_EXPLICIT
#define TYPE_VIS __attribute__((type_visibility("default")))
#else
#define TYPE_VIS
#endif

namespace __cxxabiv1 {
class TYPE_VIS __fundamental_type_info {
  __attribute__((visibility("hidden"))) virtual ~__fundamental_type_info();
};

__fundamental_type_info::~__fundamental_type_info() {}

} // namespace __cxxabiv1


























