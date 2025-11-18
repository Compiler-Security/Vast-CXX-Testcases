// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++98 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

#if __cplusplus >= 201103L
int InitRefWithList() { static const int &r = {123}; return r; }
#endif

struct XPTParamDescriptor {};
struct nsXPTParamInfo {
  nsXPTParamInfo(const XPTParamDescriptor& desc);
};
void a(XPTParamDescriptor *params) {
  const nsXPTParamInfo& paramInfo = params[0];
}

namespace PR5911 {
  template <typename T, int N> int f(const T (&a)[N]) { return N; }
  int iarr[] = { 1 };
  int test() { return f(iarr); }
}

struct Foo { int foo; };
Foo& ignoreSetMutex = *(new Foo);

struct { int bitfield : 3; } s = { 3 };
const int &s2 = s.bitfield;

struct SelfReference { SelfReference &r; };
extern SelfReference self_reference_1;
SelfReference self_reference_2 = {self_reference_1};
