// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

#pragma weak zex
int zex;

#pragma weak foo
struct S {  void foo(); };
void S::foo() {}

#pragma weak zed
namespace bar {  void zed() {} }

#pragma weak bah
void bah() {}

#pragma weak baz
extern "C" void baz() {}

#pragma weak _Z3baxv
void bax() {}
