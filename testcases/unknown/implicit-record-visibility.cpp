// RUN: %driver -cc1 %isys %s -I%S -fvisibility=hidden %target -o %t%output-suffix && %filecheck

#include <stdarg.h>
#include <typeinfo>


void f(va_list) { (void)typeid(f); }
