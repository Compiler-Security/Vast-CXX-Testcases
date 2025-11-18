// RUN: %driver -cc1 %isys -no-enable-noundef-analysis -std=c++03 -fexceptions -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -no-enable-noundef-analysis -std=c++03 %s %target -o %t%output-suffix && %filecheck

struct POD {
  int w, x, y, z;
};

struct PODLike {
  int w, x, y, z;
  PODLike();
  ~PODLike();
};

struct NonPOD {
  NonPOD();
  NonPOD(const NonPOD&);
  NonPOD& operator=(const NonPOD&);
};

struct Basic {
  int a, b, c, d;
  NonPOD np;
  int w, x, y, z;
};

struct PODMember {
  int a, b, c, d;
  POD p;
  NonPOD np;
  int w, x, y, z;
};

struct PODLikeMember {
  int a, b, c, d;
  PODLike pl;
  NonPOD np;
  int w, x, y, z;
};

struct ArrayMember {
  int a, b, c, d;
  int e[12];
  NonPOD np;
  int f[12];
  int w, x, y, z;
};

struct ZeroLengthArrayMember {
    NonPOD np;
    int a;
    int b[0];
    int c;
};

struct VolatileMember {
  int a, b, c, d;
  volatile int v;
  NonPOD np;
  int w, x, y, z;
};

struct BitfieldMember {
  int a, b, c, d;
  NonPOD np;
  int w : 6;
  int x : 6;
  int y : 6;
  int z : 6;
};

struct BitfieldMember2 {
  unsigned a : 1;
  unsigned b, c, d;
  NonPOD np;
};

struct BitfieldMember3 {
  virtual void f();
  int   : 8;
  int x : 1;
  int y;
};

struct InnerClassMember {
  struct {
    int a, b, c, d;
  } a;
  int b, c, d, e;
  NonPOD np;
  int w, x, y, z;
};

struct ReferenceMember {
  ReferenceMember(int &a, int &b, int &c, int &d)
    : a(a), b(b), c(c), d(d) {}
  int &a;
  int &b;
  NonPOD np;
  int &c;
  int &d;
};

struct __attribute__((packed)) PackedMembers {
  char c;
  NonPOD np;
  int w, x, y, z;
};



#define CALL_AO(T) void callAO##T(T& a, const T& b) { a = b; } 

CALL_AO(Basic)
CALL_AO(PODMember)
CALL_AO(PODLikeMember)
CALL_AO(ArrayMember)
CALL_AO(ZeroLengthArrayMember)
CALL_AO(VolatileMember)
CALL_AO(BitfieldMember)
CALL_AO(InnerClassMember)
CALL_AO(PackedMembers)












#define CALL_CC(T) T callCC##T(const T& b) { return b; }

CALL_CC(PackedMembers)

CALL_CC(BitfieldMember2)

CALL_CC(BitfieldMember3)

CALL_CC(ReferenceMember)

CALL_CC(InnerClassMember)

CALL_CC(BitfieldMember)

CALL_CC(VolatileMember)

CALL_CC(ArrayMember)

CALL_CC(PODLikeMember)

CALL_CC(PODMember)

CALL_CC(Basic)
