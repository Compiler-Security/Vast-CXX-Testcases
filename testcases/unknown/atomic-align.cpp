// RUN: %driver -cc1 %isys %s -std=c++14 %target -o %t%output-suffix && %filecheck

struct AM {
  int f1, f2;
};
alignas(8) AM m;
AM load1() {
  AM am;
  __atomic_load(&m, &am, 0);
  return am;
}

struct BM {
  int f1;
  alignas(8) AM f2;
};
BM bm;
AM load2() {
  AM am;
  __atomic_load(&bm.f2, &am, 0);
  return am;
}

namespace std {
  template <class _Tp>
  inline constexpr
  __attribute__ ((__visibility__("hidden"), __internal_linkage__))
  _Tp* __addressof(_Tp& __x) noexcept
  {
      return __builtin_addressof(__x);
  }
}

AM load3() {
  AM am;
  __atomic_load(std::__addressof(m), &am, 0);
  return am;
}
