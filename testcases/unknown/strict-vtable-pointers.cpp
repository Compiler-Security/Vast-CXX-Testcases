// RUN: %driver -cc1 %isys %s -I%S -fstrict-vtable-pointers -std=c++11 %target -o %t%output-suffix && %filecheck

typedef __typeof__(sizeof(0)) size_t;
void *operator new(size_t, void *) throw();
using uintptr_t = unsigned long long;

struct NotTrivialDtor {
  ~NotTrivialDtor();
};

struct DynamicBase1 {
  NotTrivialDtor obj;
  virtual void foo();
};

struct DynamicDerived : DynamicBase1 {
  void foo() override;
};

struct DynamicBase2 {
  virtual void bar();
  ~DynamicBase2() {
    bar();
  }
};

struct DynamicDerivedMultiple : DynamicBase1, DynamicBase2 {
  void foo() override;
  void bar() override;
};

struct StaticBase {
  NotTrivialDtor obj;
  void bar();
};

struct DynamicFromStatic : StaticBase {
  virtual void bar();
};

struct DynamicFromVirtualStatic1 : virtual StaticBase {
};

struct DynamicFromVirtualStatic2 : virtual StaticBase {
};

struct DynamicFrom2Virtuals : DynamicFromVirtualStatic1,
                              DynamicFromVirtualStatic2 {
};

void LocalObjects() {
  DynamicBase1 DB;
  DB.foo();
  DynamicDerived DD;
  DD.foo();

  DynamicBase2 DB2;
  DB2.bar();

  StaticBase SB;
  SB.bar();

  DynamicDerivedMultiple DDM;
  DDM.foo();
  DDM.bar();

  DynamicFromStatic DFS;
  DFS.bar();
  DynamicFromVirtualStatic1 DFVS1;
  DFVS1.bar();
  DynamicFrom2Virtuals DF2V;
  DF2V.bar();
}

struct DynamicFromVirtualStatic1;

struct DynamicFrom2Virtuals;


void Pointers1() {
  DynamicBase1 *DB = new DynamicBase1;
  DB->foo();

  DynamicDerived *DD = new (DB) DynamicDerived;
  DD->foo();
  DD->~DynamicDerived();
}

void HackingObjects() {
  DynamicBase1 DB;
  DB.foo();

  DynamicDerived *DB2 = new (&DB) DynamicDerived;
  DB2->foo();
  DB2->~DynamicDerived();

  new (&DB) DynamicBase1;
  DB.foo();
}

/*** Testing Constructors ***/
struct DynamicBase1;

struct DynamicDerived;



struct DynamicDerivedMultiple;






struct DynamicFromStatic;

struct A {
  virtual void foo();
  int m;
};
struct B : A {
  void foo() override;
};

union U {
  A a;
  B b;
};

void changeToB(U *u);
void changeToA(U *u);

void g2(A *a) {
  a->foo();
}
void UnionsBarriers(U *u) {
  changeToB(u);
  g2(&u->b);
  changeToA(u);
  g2(&u->a);
}

struct HoldingVirtuals {
  A a;
};

struct Empty {};
struct AnotherEmpty {
  Empty e;
};
union NoVptrs {
  int a;
  AnotherEmpty empty;
};
void take(AnotherEmpty &);

void noBarriers(NoVptrs &noVptrs) {
  noVptrs.a += 42;
  take(noVptrs.empty);
}

union U2 {
  HoldingVirtuals h;
  int z;
};
void take(HoldingVirtuals &);

void UnionsBarriers2(U2 &u) {
  u.z += 42;
  take(u.h);
}

struct VirtualInBase : HoldingVirtuals, Empty {
};

struct VirtualInVBase : virtual Empty, virtual HoldingVirtuals {
};

struct VirtualInheritance : virtual Empty {
};

union U3 {
  VirtualInBase v1;
  VirtualInBase v2;
  VirtualInheritance v3;
  int z;
};

void take(VirtualInBase &);
void take(VirtualInVBase &);
void take(VirtualInheritance &);

void UnionsBarrier3(U3 &u) {
  u.z += 42;
  take(u.v1);
  take(u.v2);

  take(u.v3);
}

void compare() {
  A *a = new A;
  a->foo();
  A *b = new (a) B;

  if (a == b)
    b->foo();
}

bool compare2(A *a, A *a2) {
  return a < a2;
}
bool compareIntPointers(int *a, int *b) {
  return a == b;
}

struct HoldingOtherVirtuals {
  B b;
};

bool compare5(HoldingOtherVirtuals *a, HoldingOtherVirtuals *b) {
  return a == b;
}
bool compareNull(A *a) {

  if (a != nullptr)
    return false;
  if (!a)
    return false;
  return a == nullptr;
}

struct X;
bool compare4(X *x, X *x2) {
  return x == x2;
}

void member1(HoldingOtherVirtuals *p) {

  (void)p->b;
}

void member2(A *a) {
  (void)a->m;
}

void testCompareMembers() {

  A *ap = new A;
  ap->foo();
  int *const apm = &ap->m;

  B *bp = new (ap) B;

  int *const bpm = &bp->m;

  if (apm == bpm) {
    bp->foo();
  }
}

void testCast1(A *a) {
  auto *v = (void *)a;

  auto i2 = (uintptr_t)a;
  (void)i2;


  auto i = (uintptr_t)v;
}

struct Incomplete;
void testCast2(Incomplete *I) {
  auto *v = (void *)I;

  auto i2 = (uintptr_t)I;
  (void)i2;


  auto i = (uintptr_t)v;
}

void testCast3(uintptr_t i) {
  A *a3 = (A *)i;
  (void)a3;

  auto *v2 = (void *)i;

  A *a2 = (A *)v2;
  (void)a2;

  auto *v3 = (void *)i;
  (void)v3;
}

void testCast4(uintptr_t i) {
  auto *a3 = (Incomplete *)i;
  (void)a3;

  auto *v2 = (void *)i;
  auto *a2 = (Incomplete *)v2;
  (void)a2;
}

void testCast5(B *b) {
  A *a = b;
  (void)a;

  auto *b2 = (B *)a;
  (void)b2;
}

void testCast6(A *a) {

  auto *I = (Incomplete *)a;
  (void)I;
  auto *a2 = (A *)I;
  (void)a2;

  auto *E = (Empty *)a;
  (void)E;

  auto *a3 = (A *)E;
  (void)a3;

  auto i = (uintptr_t)E;
  (void)i;
}

class Incomplete2;
void testCast7(Incomplete *I) {


  auto *I2 = (Incomplete2 *)I;
  (void)I2;
}

template <typename Base>
struct PossiblyDerivingFromDynamicBase : Base {
};

void testCast8(Incomplete *I) {
  auto *P = (PossiblyDerivingFromDynamicBase<Incomplete> *)I;
  (void)P;

  auto *P2 = (PossiblyDerivingFromDynamicBase<Empty> *)I;
  (void)P2;

  auto *P3 = (PossiblyDerivingFromDynamicBase<A> *)I;
  (void)P3;

  auto *a3 = (A *)P3;

}

void testCast9(PossiblyDerivingFromDynamicBase<Incomplete> *P) {
  auto *V = (void *)P;

}

/** DTORS **/








