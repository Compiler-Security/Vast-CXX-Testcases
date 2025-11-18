// RUN: %driver -cc1 %isys -fms-extensions -w %s %target -o %t%output-suffix && %filecheck


struct NonTrivial {
  NonTrivial();
  NonTrivial(const NonTrivial &o);
  int x;
};

struct __declspec(align(64)) OverAligned {
  OverAligned();
  int buf[16];
};

struct __declspec(align(8)) Both {
  Both();
  Both(const Both &o);
  int x, y;
};

extern int gvi32;

int receive_inalloca_overaligned(NonTrivial nt, OverAligned o) {
  return nt.x + o.buf[0];
}


int pass_inalloca_overaligned() {
  gvi32 = receive_inalloca_overaligned(NonTrivial(), OverAligned());
  return gvi32;
}





int receive_both(Both o) {
  return o.x + o.y;
}


int pass_both() {
  gvi32 = receive_both(Both());
  return gvi32;
}


int receive_inalloca_both(NonTrivial nt, Both o) {
  return nt.x + o.x + o.y;
}


int pass_inalloca_both() {
  gvi32 = receive_inalloca_both(NonTrivial(), Both());
  return gvi32;
}


struct [[trivial_abi]] alignas(8) MyPtr {
  MyPtr();
  MyPtr(const MyPtr &o);
  ~MyPtr();
  int *ptr;
};

int receiveMyPtr(MyPtr o) { return *o.ptr; }


int passMyPtr() { return receiveMyPtr(MyPtr()); }

