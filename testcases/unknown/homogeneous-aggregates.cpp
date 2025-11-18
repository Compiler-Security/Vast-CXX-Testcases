// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -mfloat-abi hard %s %target -o %t%output-suffix && %filecheck

#if defined(__x86_64__)
#define CC __attribute__((vectorcall))
#else
#define CC
#endif


struct Base1 {
  int x;
};
struct Base2 {
  double x;
};
struct Base3 {
  double x;
};
struct D1 : Base1 {  // non-homogeneous aggregate
  double y, z;
};
struct D2 : Base2 {  // homogeneous aggregate
  double y, z;
};
struct D3 : Base1, Base2 {  // non-homogeneous aggregate
  double y, z;
};
struct D4 : Base2, Base3 {  // homogeneous aggregate
  double y, z;
};

struct I1 : Base2 {};
struct I2 : Base2 {};
struct I3 : Base2 {};
struct D5 : I1, I2, I3 {}; // homogeneous aggregate

D1 CC func_D1(D1 x) { return x; }

D2 CC func_D2(D2 x) { return x; }

D3 CC func_D3(D3 x) { return x; }

D4 CC func_D4(D4 x) { return x; }

D5 CC func_D5(D5 x) { return x; }


void call_D5(D5 *p) {
  func_D5(*p);
}


struct Empty { };
struct Float1 { float x; };
struct Float2 { float y; };
struct HVAWithEmptyBase : Float1, Empty, Float2 { float z; };

void CC with_empty_base(HVAWithEmptyBase a) {}


struct HVAWithEmptyBitField : Float1, Float2 {
  int : 0; // Takes no space.
  float z;
};

void CC with_empty_bitfield(HVAWithEmptyBitField a) {}

namespace pr47611 {

struct Pod {
  double b[2];
};
struct NotCXX14Aggregate {
  NotCXX14Aggregate();
  Pod p;
};
struct NotPod {
  NotCXX14Aggregate x;
};
struct Empty {};
struct HasEmptyBase : public Empty {
  double b[2];
};
struct HasPodBase : public Pod {};
Pod copy(Pod *x) { return *x; } // MSVC: ldp d0,d1,[x0], Clang: ldp d0,d1,[x0]
NotCXX14Aggregate copy(NotCXX14Aggregate *x) { return *x; } // MSVC: stp x8,x9,[x0], Clang: str q0,[x0]
NotPod copy(NotPod *x) { return *x; }
HasEmptyBase copy(HasEmptyBase *x) { return *x; }
HasPodBase copy(HasPodBase *x) { return *x; }

void call_copy_pod(Pod *pod) {
  *pod = copy(pod);
}

void call_copy_notcxx14aggregate(NotCXX14Aggregate *notcxx14aggregate) {
  *notcxx14aggregate = copy(notcxx14aggregate);
}

void call_copy_notpod(NotPod *notPod) {
  *notPod = copy(notPod);
}

void call_copy_hasemptybase(HasEmptyBase *hasEmptyBase) {
  *hasEmptyBase = copy(hasEmptyBase);
}

void call_copy_haspodbase(HasPodBase *hasPodBase) {
  *hasPodBase = copy(hasPodBase);
}
} // namespace pr47611

namespace protected_member {
struct HFA {
  double x;
  double y;
protected:
  double z;
};
double foo(HFA v) { return v.x + v.y; }
}
namespace private_member {
struct HFA {
  double x;
  double y;
private:
  double z;
};
double foo(HFA v) { return v.x + v.y; }
}
namespace polymorphic {
struct NonHFA {
  double x;
  double y;
  double z;
  virtual void f1();
};
double foo(NonHFA v) { return v.x + v.y; }
}
namespace trivial_copy_assignment {
struct HFA {
  double x;
  double y;
  double z;
  HFA &operator=(const HFA&) = default;
};
double foo(HFA v) { return v.x + v.y; }
}
namespace non_trivial_copy_assignment {
struct NonHFA {
  double x;
  double y;
  double z;
  NonHFA &operator=(const NonHFA&);
};
double foo(NonHFA v) { return v.x + v.y; }
}
namespace user_provided_ctor {
struct HFA {
  double x;
  double y;
  double z;
  HFA(int);
};
double foo(HFA v) { return v.x + v.y; }
}
namespace trivial_dtor {
struct HFA {
  double x;
  double y;
  double z;
  ~HFA() = default;
};
double foo(HFA v) { return v.x + v.y; }
}
namespace non_trivial_dtor {
struct NonHFA {
  double x;
  double y;
  double z;
  ~NonHFA();
};
double foo(NonHFA v) { return v.x + v.y; }
}
namespace non_empty_base {
struct non_empty_base { double d; };
struct HFA : non_empty_base {
  double x;
  double y;
  double z;
};
double foo(HFA v) { return v.x + v.y; }
}
namespace empty_field {
struct empty { };
struct NonHFA {
  double x;
  double y;
  double z;
  empty e;
};
double foo(NonHFA v) { return v.x + v.y; }
}
namespace non_empty_field {
struct non_empty { double d; };
struct HFA {
  double x;
  double y;
  double z;
  non_empty e;
};
double foo(HFA v) { return v.x + v.y; }
}

namespace pr62223 {
typedef double V __attribute((ext_vector_type(2)));
struct base { V v; };
struct test : base { test(double); protected: V v2;};
test f(test *x) { return *x; }

struct base2 { double v; };
struct test2 : base2 { test2(double); protected: double v2;};
test2 f(test2 *x) { return *x; }
}
