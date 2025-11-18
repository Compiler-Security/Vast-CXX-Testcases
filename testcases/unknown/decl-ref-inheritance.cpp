// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct foo {
  float val;
};

template <typename T> struct bar : T {
};

struct baz : bar<foo> {
  float get() {
    return val;
  }
};

int qux() {
  auto f = baz{};
  return f.get();
}

struct f {
  void *g;
};

template <typename j> struct k : j {
  virtual void l(){ (void)f::g; }
};

k<f> q;

class Base {
protected:
  int member;
};

template <typename Parent>
struct Subclass : public Parent {
  int func() { return Base::member; }
};

using Impl = Subclass<Base>;

int use() {
  Impl i;
  return i.func();
}
