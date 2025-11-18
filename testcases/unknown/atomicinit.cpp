// RUN: %driver -cc1 %isys -fno-inline-functions %s -std=c++11 %target -o %t%output-suffix && %filecheck

typedef _Atomic(int) AtomicInt;
AtomicInt PR22043 = AtomicInt();


struct A {
  _Atomic(int) i;
  A(int j);
  void v(int j);
};
void A::v(int j) { i = j; }
A::A(int j) : i(j) {}

struct B {
  int i;
  B(int x) : i(x) {}
};

_Atomic(B) b;

void atomic_init(A& a, int i) {
  __c11_atomic_init(&b, B(i));
}

void atomic_init_bool(_Atomic(bool) *ab, bool b) {
  __c11_atomic_init(ab, b);
}

struct AtomicBoolMember {
  _Atomic(bool) ab;
  AtomicBoolMember(bool b);
};

AtomicBoolMember::AtomicBoolMember(bool b) : ab(b) { }

namespace PR18097 {
  namespace dynamic {
    struct X {
      X(int);
      short n;
      char c;
    };

    _Atomic(X) a = X(1);

    _Atomic(X) b(X(2));

    _Atomic(X) c{X(3)};

    struct Y {
      _Atomic(X) a;
      _Atomic(int) b;
    };
    Y y = { X(4), 5 };
  }

  namespace constant {
    struct X {
      constexpr X(int n) : n(n) {}
      short n;
      char c = 6;
    };
    _Atomic(X) a = X(1);
    _Atomic(X) b(X(2));
    _Atomic(X) c{X(3)};

    struct Y {
      _Atomic(X) a;
      _Atomic(int) b;
    };
    Y y = { X(4), 5 };

    int z;
    constexpr X x{1};
    Y y2 = { x, z };

    typedef union {
      unsigned int f0;
    } Union0;

    typedef struct {
      _Atomic(Union0) f1;
    } Struct0;

    Struct0 g = {};
  }
}
