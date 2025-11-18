// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -mdefault-visibility-export-mapping=none %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -mdefault-visibility-export-mapping=explicit %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -mdefault-visibility-export-mapping=all %target -o %t%output-suffix && %filecheck

struct A {};

template <class T>
class B {
public:
  T x;
  B(T _x) : x(_x) {}
  ~B() {}
  void func(T x) {}
};

template <class T>
class __attribute__((visibility("default"))) C {
public:
  T x;
  C(T _x) : x(_x) {}
  ~C() {}
  void func(T x) {}
};

class D {
public:
  ~D();
};

D::~D() {}

extern template class B<int>;
extern template class C<int>;

void func() {
  B<A> x({});
  C<A> y({});
  x.func({});
  y.func({});
  B<int> xi(0);
  C<int> yi(0);
  xi.func(0);
  yi.func(0);
  D z;
}



















