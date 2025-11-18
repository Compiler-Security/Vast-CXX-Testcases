// RUN: %driver -cc1 %isys -I%S %s -fcxx-exceptions -fexceptions %target -o %t%output-suffix && %filecheck
struct A { virtual void f(); };
struct B : A { };

B fail;
const B& f(A *a) {
  try {
    dynamic_cast<const B&>(*a);
  } catch (...) {
  }
  return fail;
}


