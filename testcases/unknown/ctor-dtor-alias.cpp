// RUN: %driver -cc1 %isys %s -mconstructor-aliases %target -o %t%output-suffix && %filecheck



namespace test1 {



template <typename T>
struct foobar {
  foobar() {}
  virtual ~foobar() {}
};

template struct foobar<void>;
}

namespace test2 {

void g();
template <typename T> struct foobar {
  foobar() { g(); }
};
foobar<void> x;
}

namespace test3 {

namespace {
struct A {
  ~A() {}
};

struct B : public A {};
}

B x;
}

namespace test4 {


  struct A {
    virtual ~A() {}
  };
  struct B : public A{
    ~B() {}
  };
  B X;
}

namespace test5 {

  struct A {
    virtual ~A() {}
  };
  namespace {
  struct B : public A{
    ~B() {}
  };
  }
  B X;
}

namespace test6 {
  struct A {
    virtual ~A();
  };
  namespace {
  struct B : public A {
    ~B() {}
  };
  }
  B X;
}

namespace test7 {
  template <typename> struct A {
    ~A() {}
  };
  class B : A<int> {
    ~B();
  };
  template class A<int>;
  B::~B() {}
}

namespace test8 {
  struct foo {
    ~foo();
  };
  foo::~foo() {}
  struct bar : public foo {
    ~bar();
  };
  bar::~bar() {}
  struct zed : public bar {};
  zed foo;
}

namespace test9 {
struct foo {
  __attribute__((stdcall)) ~foo() {
  }
};

struct bar : public foo {};

void zed() {
  bar ptr;
}
}


class A {
public:
  A(int);
  virtual ~A();
};

template <class>
class B : A {
public:
  B()
      : A(0) {
  }
  __attribute__((always_inline)) ~B() {
  }
};

extern template class B<char>;

class C : B<char> {
};

void
fn1() {
  new C;
}

namespace test10 {
struct bar {
  ~bar();
};
bar::~bar() {
}
} // closing the namespace causes ~bar to be sent to CodeGen
namespace test10 {
template <typename T>
struct foo : public bar {
  ~foo();
};
template <typename T>
foo<T>::~foo() {}
template class foo<int>;
}

namespace test11 {
struct bar {
  ~bar();
};
bar::~bar() {}
struct foo : public bar {
  ~foo();
};
foo::~foo() {}
}

namespace test12 {
template <int>
struct foo {
  ~foo() { delete this; }
};

template class foo<1>;
}
