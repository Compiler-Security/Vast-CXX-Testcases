// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace PR11411 {
  template<typename _Tp> struct Ptr {
    void f();
  };

  template<typename _Tp> inline void Ptr<_Tp>::f() {
    int* _refcount;
    __sync_fetch_and_add(_refcount, 1);
  }
  void f(Ptr<int> *a) { a->f(); }
}

namespace DelegatingParameter {
  struct Z { int z[100]; };
  struct S { S(_Atomic Z); };
  S::S(_Atomic Z) {}
}
