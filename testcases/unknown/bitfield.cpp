// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace N0 {
  struct __attribute__((packed)) S {
    unsigned b00 : 14;
    unsigned b01 : 2;
    unsigned b20 : 6;
    unsigned b21 : 2;
    unsigned b30 : 30;
    unsigned b31 : 2;
    unsigned b70 : 6;
    unsigned b71 : 2;
  };
  unsigned read00(S* s) {
    return s->b00;
  }
  unsigned read01(S* s) {
    return s->b01;
  }
  unsigned read20(S* s) {
    return s->b20;
  }
  unsigned read21(S* s) {
    return s->b21;
  }
  unsigned read30(S* s) {
    return s->b30;
  }
  unsigned read31(S* s) {
    return s->b31;
  }
  unsigned read70(S* s) {
    return s->b70;
  }
  unsigned read71(S* s) {
    return s->b71;
  }
}

namespace N1 {
  struct S {
    char a;
    unsigned b : 1;
    char c;
  };
  unsigned read(S* s) {
    return s->b;
  }
  void write(S* s, unsigned x) {
    s->b = x;
  }
}

namespace N2 {
  struct S {
    unsigned b : 24;
    void *p;
  };
  unsigned read(S* s) {
    return s->b;
  }
  void write(S* s, unsigned x) {
    s->b = x;
  }
}

namespace N3 {
  struct S {
    unsigned b : 24;
  };
  unsigned read(S* s) {
    return s->b;
  }
  void write(S* s, unsigned x) {
    s->b = x;
  }
}

namespace N4 {
  struct Base {
    virtual ~Base() {}

    unsigned b : 24;
  };
#if 0
  struct Derived : public Base {
    char c;
  };
#endif
  unsigned read(Base* s) {
    return s->b;
  }
  void write(Base* s, unsigned x) {
    s->b = x;
  }
}

namespace N5 {
  union U {
    struct X { unsigned b : 24; char c; } x;
    struct Y { unsigned b : 24; } y;
  };
  unsigned read(U* u) {
    return u->y.b;
  }
  void write(U* u, unsigned x) {
    u->y.b = x;
  }
}

namespace N6 {
  struct S {
    unsigned b1 : 24;
    unsigned char : 0;
    unsigned char b2 : 8;
  };
  unsigned read(S* s) {
    return s->b1 + s->b2;
  }
  void write(S* s, unsigned x) {
    s->b1 = x;
    s->b2 = x;
  }
}

namespace N7 {
  struct B1 {
    virtual void f();
    unsigned b1 : 24;
  };
  struct B2 : virtual B1 {
    virtual ~B2();
    unsigned b : 24;
  };
#if 0
  struct Derived : public B2 {
    char c;
  };
#endif
  unsigned read(B2* s) {
    return s->b;
  }
  void write(B2* s, unsigned x) {
    s->b = x;
  }
}
