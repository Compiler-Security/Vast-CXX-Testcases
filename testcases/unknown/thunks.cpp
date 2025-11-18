// RUN: %driver -cc1 %isys %s -funwind-tables=2 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -dwarf-version=5 -funwind-tables=2 %target -o %t%output-suffix && %filecheck




namespace Test1 {


struct A {
  virtual void f();
};

struct B {
  virtual void f();
};

struct C : A, B {
  virtual void c();

  virtual void f();
};

void C::f() { }

}

namespace Test2 {


struct A {
  virtual void f();
};

struct B : virtual A {
  virtual void b();
  virtual void f();
};

void B::f() { }


}

namespace Test3 {


struct V1 { };
struct V2 : virtual V1 { };

struct A {
  virtual V1 *f();
};

struct B : A {
  virtual void b();

  virtual V2 *f();
};

V2 *B::f() { return 0; }

}

namespace Test4 {


struct A {
  virtual void f();
};

struct B {
  virtual void f();
};

struct __attribute__((visibility("protected"))) C : A, B {
  virtual void c();

  virtual void f();
};

void C::f() { }

}

namespace Test4B {
  struct A {
    virtual void f();
  };

  struct B {
    virtual void f();
  };

  namespace {
    struct C : A, B {
      virtual void c();
      virtual void f();
    };
  }
  void C::c() {}
  void C::f() {}

  void f() {
    C c;
    c.f();
  }
}

namespace Test5 {

struct A {
  virtual void f();
};

struct B : virtual A {
  virtual void f() { }
};

void f(B b) {
  b.f();
}
}

namespace Test6 {
  struct X {
    X();
    X(const X&);
    X &operator=(const X&);
    ~X();
  };

  struct P {
    P();
    P(const P&);
    ~P();
    X first;
    X second;
  };

  P getP();

  struct Base1 {
    int i;

    virtual X f() { return X(); }
  };

  struct Base2 {
    float real;

    virtual X f() { return X(); }
  };

  struct Thunks : Base1, Base2 {
    long l;

    virtual X f();
  };

  X Thunks::f() { return X(); }

}

namespace Test7 {
  struct X {
    X();
    X(const X&);
    X &operator=(const X&);
    ~X();
  };

  struct Small { short s; };
  struct Large {
    char array[1024];
  };

  class A {
  protected:
    virtual void foo() = 0;
  };

  class B : public A {
  protected:
    virtual void bar() = 0;
  };

  class C : public A  {
  protected:
    virtual void baz(X, X&, _Complex float, Small, Small&, Large) = 0;
  };

  class D : public B,
            public C {

    void foo() {}
    void bar() {}
    void baz(X, X&, _Complex float, Small, Small&, Large);
  };

  void D::baz(X, X&, _Complex float, Small, Small&, Large) { }

  void testD() { D d; }

}

namespace Test8 {
  struct NonPOD { ~NonPOD(); int x, y, z; };
  struct A { virtual void foo(); };
  struct B { virtual void bar(NonPOD); };
  struct C : A, B { virtual void bar(NonPOD); static void helper(NonPOD); };

  void C::helper(NonPOD var) {}

  void C::bar(NonPOD var) {}

}

namespace Test9 {
  struct A { virtual ~A() { } };
  struct B : A { virtual void test() const {} };
  struct C : B { C(); ~C(); };
  struct D : C { D() {} };
  void test() {
    D d;
  }
}

namespace Test10 {
  struct A { virtual void foo(); };
  struct B { virtual void foo(); };
  struct C : A, B { void foo() {} };

  void test() {
    C c;
  }
}

namespace Test11 {
  struct A {             virtual A* f(); };
  struct B : virtual A { virtual A* f(); };
  struct C : B         { virtual C* f(); };
  C* C::f() { return 0; }





}

namespace Test12 {
  struct A {
    virtual A* f(int x, ...);
  };
  struct B {
    virtual B* f(int x, ...);
  };
  struct C : A, B {
    virtual void c();
    virtual C* f(int x, ...);
  };
  C* makeC();
  C* C::f(int x, ...) { return makeC(); }



  C c;
}

namespace Test13 {
  struct B1 {
    virtual B1 &foo1();
  };
  struct Pad1 {
    virtual ~Pad1();
  };
  struct Proxy1 : Pad1, B1 {
    virtual ~Proxy1();
  };
  struct D : virtual Proxy1 {
    virtual ~D();
    virtual D &foo1();
  };
  D& D::foo1() {
    return *this;
  }

}

namespace Test14 {
  class A {
    virtual void f();
  };
  class B {
    virtual void f();
  };
  class C : public A, public B  {
    virtual void f();
  };
  void C::f() {
  }
}

namespace Test15 {
  struct A {
    virtual ~A();
  };
  struct B {
    virtual void f(int x, ...);
  };
  struct C : A, B {
    virtual void c();
    virtual void f(int x, ...);
  };
  void C::c() {}



}

namespace Test16 {
struct A {
  virtual ~A();
};
struct B {
  virtual void foo();
};
struct C : public A, public B {
  void foo() {}
};
struct D : public C {
  ~D();
};
D::~D() {}
}

namespace Test17 {
class A {
  virtual void f(const char *, ...);
};
class B {
  virtual void f(const char *, ...);
};
class C : A, B {
  virtual void anchor();
  void f(const char *, ...) override;
};
void C::anchor() {}
C c;



}

/**** The following has to go at the end of the file ****/








