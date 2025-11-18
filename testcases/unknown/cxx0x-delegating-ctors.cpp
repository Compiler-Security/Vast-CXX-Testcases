// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct non_trivial {
  non_trivial();
  ~non_trivial() noexcept(false);
};
non_trivial::non_trivial() {}
non_trivial::~non_trivial() noexcept(false) {}

struct delegator {
  non_trivial n; 
  delegator();
  delegator(int);
  delegator(char);
  delegator(bool);
};

delegator::delegator() {
  throw 0;
}


delegator::delegator(bool)
{}


delegator::delegator(char)
  : delegator(true) {
  throw 0;
}


delegator::delegator(int)
  : delegator()
{}

namespace PR12890 {
  class X {
    int x;
    X() = default;
    X(int);
  };
  X::X(int) : X() {}
}

namespace PR14588 {
  void other();

  class Base {
  public:
    Base() { squawk(); }
    virtual ~Base() {}

    virtual void squawk() { other(); }
  };


  class Foo : public virtual Base {
  public:
    Foo();
    Foo(const void * inVoid);
    virtual ~Foo() {}

    virtual void squawk() { other(); }
  };


  Foo::Foo() : Foo(__null) { other(); }
  Foo::Foo(const void *inVoid) {
    squawk();
  }

}
