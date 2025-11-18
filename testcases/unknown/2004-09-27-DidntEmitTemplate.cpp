// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct Pass {};

template<typename PassName>
Pass *callDefaultCtor() { return new Pass(); }

void foo(Pass *(*C)());

struct basic_string {
  bool empty() const { return true; }
};


bool foo2(basic_string &X) {
  return X.empty();
}
void baz() { foo(callDefaultCtor<Pass>); }
