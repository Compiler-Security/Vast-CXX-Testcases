// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++98 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

class A { protected: virtual ~A() {} };
class B { protected: virtual ~B() {} };

class C : A { char x; };
class D : public A { short y; };
class E : public A, public B { int z; };
class F : public virtual A { long long w; };
class G : virtual A { long long w; };

class H : public E { int a; };
class I : public F { char b; };

class J : public H { char q; };
class K : public C, public B { char q; };

class XA : public A { };
class XB : public A { };
class XC : public virtual A { };
class X : public XA, public XB, public XC { };

void test(A *a, B *b) {
  volatile C *ac = dynamic_cast<C *>(a);
  volatile D *ad = dynamic_cast<D *>(a);
  volatile E *ae = dynamic_cast<E *>(a);
  volatile F *af = dynamic_cast<F *>(a);
  volatile G *ag = dynamic_cast<G *>(a);
  volatile H *ah = dynamic_cast<H *>(a);
  volatile I *ai = dynamic_cast<I *>(a);
  volatile J *aj = dynamic_cast<J *>(a);
  volatile K *ak = dynamic_cast<K *>(a);
  volatile X *ax = dynamic_cast<X *>(a);

  volatile E *be = dynamic_cast<E *>(b);
  volatile G *bg = dynamic_cast<G *>(b);
  volatile J *bj = dynamic_cast<J *>(b);
  volatile K *bk = dynamic_cast<K *>(b);
}
