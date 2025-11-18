// RUN: %driver -cc1 %isys -I%S %s -fcxx-exceptions -fexceptions -std=c++11 %target -o %t%output-suffix && %filecheck
struct A { virtual ~A(); };
struct B final : A { };
struct C { virtual ~C(); int c; };

A *nonnull1(C* c) {
  return dynamic_cast<A*>(c);
}

C *nonnull2(A* a) {
  return dynamic_cast<C*>(a);
}

C *f(B* b) {
  return dynamic_cast<C*>(b);
}

C &f(B& b) {
  return dynamic_cast<C&>(b);
}

B *g(C* c) {
  return dynamic_cast<B*>(c);
}

B &g(C& c) {
  return dynamic_cast<B&>(c);
}

void dont_crash() {
  (void) dynamic_cast<void*>((A*)0);
  (void) dynamic_cast<void*>((B*)0);
}

