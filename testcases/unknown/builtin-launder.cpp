// RUN: %driver -cc1 %isys -fstrict-vtable-pointers %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct TestVirtualFn {
  virtual void foo() {}
};

extern "C" void test_builtin_launder_virtual_fn(TestVirtualFn *p) {



  TestVirtualFn *d = __builtin_launder(p);
}

struct TestPolyBase : TestVirtualFn {
};

extern "C" void test_builtin_launder_poly_base(TestPolyBase *p) {


  TestPolyBase *d = __builtin_launder(p);
}

struct TestBase {};
struct TestVirtualBase : virtual TestBase {};

extern "C" void test_builtin_launder_virtual_base(TestVirtualBase *p) {


  TestVirtualBase *d = __builtin_launder(p);
}


extern "C" void test_builtin_launder_ommitted_one(int *p) {
  int *d = __builtin_launder(p);
}

struct TestNoInvariant {
  int x;
};

extern "C" void test_builtin_launder_ommitted_two(TestNoInvariant *p) {
  TestNoInvariant *d = __builtin_launder(p);
}

struct TestVirtualMember {
  TestVirtualFn member;
};

extern "C" void test_builtin_launder_virtual_member(TestVirtualMember *p) {
  TestVirtualMember *d = __builtin_launder(p);
}

struct TestVirtualMemberDepth2 {
  TestVirtualMember member;
};

extern "C" void test_builtin_launder_virtual_member_depth_2(TestVirtualMemberDepth2 *p) {
  TestVirtualMemberDepth2 *d = __builtin_launder(p);
}

struct TestVirtualReferenceMember {
  TestVirtualFn &member;
};

extern "C" void test_builtin_launder_virtual_reference_member(TestVirtualReferenceMember *p) {
  TestVirtualReferenceMember *d = __builtin_launder(p);
}

struct TestRecursiveMember {
  TestRecursiveMember() : member(*this) {}
  TestRecursiveMember &member;
};

extern "C" void test_builtin_launder_recursive_member(TestRecursiveMember *p) {
  TestRecursiveMember *d = __builtin_launder(p);
}

struct TestVirtualRecursiveMember {
  TestVirtualRecursiveMember() : member(*this) {}
  TestVirtualRecursiveMember &member;
  virtual void foo();
};

extern "C" void test_builtin_launder_virtual_recursive_member(TestVirtualRecursiveMember *p) {
  TestVirtualRecursiveMember *d = __builtin_launder(p);
}

extern "C" void test_builtin_launder_array(TestVirtualFn (&Arr)[5]) {
  TestVirtualFn *d = __builtin_launder(Arr);
}

extern "C" void test_builtin_launder_array_nested(TestVirtualFn (&Arr)[5][2]) {
  using RetTy = TestVirtualFn(*)[2];
  RetTy d = __builtin_launder(Arr);
}

extern "C" void test_builtin_launder_array_no_invariant(TestNoInvariant (&Arr)[5]) {
  TestNoInvariant *d = __builtin_launder(Arr);
}

extern "C" void test_builtin_launder_array_nested_no_invariant(TestNoInvariant (&Arr)[5][2]) {
  using RetTy = TestNoInvariant(*)[2];
  RetTy d = __builtin_launder(Arr);
}

template <class Member>
struct WithMember {
  Member mem;
};

template struct WithMember<TestVirtualFn[5]>;

extern "C" void test_builtin_launder_member_array(WithMember<TestVirtualFn[5]> *p) {
  auto *d = __builtin_launder(p);
}

template struct WithMember<TestVirtualFn[5][2]>;

extern "C" void test_builtin_launder_member_array_nested(WithMember<TestVirtualFn[5][2]> *p) {
  auto *d = __builtin_launder(p);
}

template struct WithMember<TestNoInvariant[5]>;

extern "C" void test_builtin_launder_member_array_no_invariant(WithMember<TestNoInvariant[5]> *p) {
  auto *d = __builtin_launder(p);
}

template struct WithMember<TestNoInvariant[5][2]>;

extern "C" void test_builtin_launder_member_array_nested_no_invariant(WithMember<TestNoInvariant[5][2]> *p) {
  auto *d = __builtin_launder(p);
}

template <class T>
struct WithBase : T {};

template struct WithBase<TestNoInvariant>;

extern "C" void test_builtin_launder_base_no_invariant(WithBase<TestNoInvariant> *p) {
  auto *d = __builtin_launder(p);
}

template struct WithBase<TestVirtualFn>;

extern "C" void test_builtin_launder_base(WithBase<TestVirtualFn> *p) {
  auto *d = __builtin_launder(p);
}

namespace pessimizing_cases {

struct TestConstMember {
  const int x;
};

extern "C" void test_builtin_launder_const_member(TestConstMember *p) {
  TestConstMember *d = __builtin_launder(p);
}

struct TestConstSubobject {
  TestConstMember x;
};

extern "C" void test_builtin_launder_const_subobject(TestConstSubobject *p) {
  TestConstSubobject *d = __builtin_launder(p);
}

struct TestConstObject {
  const struct TestConstMember x;
};

extern "C" void test_builtin_launder_const_object(TestConstObject *p) {
  TestConstObject *d = __builtin_launder(p);
}

struct TestReferenceMember {
  int &x;
};

extern "C" void test_builtin_launder_reference_member(TestReferenceMember *p) {
  TestReferenceMember *d = __builtin_launder(p);
}

} // namespace pessimizing_cases
