// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

class t {
public:
  virtual void foo(void);
  void bar(void);
  void baz(void);
};

[[gnu::aligned(16)]]
void
t::baz(void) {
}

void
t::bar(void) {
}

void
t::foo(void) {
}
