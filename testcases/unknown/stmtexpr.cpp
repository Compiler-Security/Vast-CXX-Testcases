// RUN: %driver -cc1 %isys -Wno-unused-value %s %target -o %t%output-suffix && %filecheck
extern "C" int printf(...);
extern "C" void abort();

struct A
{
  int i;
  A (int j) : i(j) {printf("this = %p A(%d)\n", this, j);}
  A (const A &j) : i(j.i) {printf("this = %p const A&(%d)\n", this, i);}
  A& operator= (const A &j) { i = j.i; abort(); return *this; }
  ~A() { printf("this = %p ~A(%d)\n", this, i); }
};

struct B
{
  int i;
  B (const A& a) { i = a.i; }
  B() {printf("this = %p B()\n", this);}
  B (const B &j) : i(j.i) {printf("this = %p const B&(%d)\n", this, i);}
  ~B() { printf("this = %p ~B(%d)\n", this, i); }
};

A foo(int j)
{
  return ({ j ? A(1) : A(0); });
}


void foo2()
{
  A b = ({ A a(1); A a1(2); A a2(3); a1; a2; a; });
  if (b.i != 1)
    abort(); 
  A c = ({ A a(1); A a1(2); A a2(3); a1; a2; a; A a3(4); a2; a3; });
  if (c.i != 4)
    abort(); 
}

void foo3()
{
  const A &b = ({ A a(1); a; });
  if (b.i != 1)
    abort();
}

void foo4()
{
  const B &b = ({ A a(1); a; });
  if (b.i != 1)
    abort();
}

int main()
{
  foo2();
  foo3();
  foo4();
  return foo(1).i-1;
}

int a[128];
int* foo5() {
  return (({ a; }));
}

int foo5(bool b) {
  int y = 0;
  y = ({ A a(1); if (b) goto G; a.i; });
  G: return y;
}

int bar(A, int);
extern "C" int cleanup_exit_scalar(bool b) {
  int v = bar(A(1), ({ if (b) return 42; 13; }));
  return v;
}


extern "C" int cleanup_exit_scalar_constant(bool b) {
  int v = (A(1), (void)({ if (b) return 42; 0; }), 13);
  return v;
}


int &getref();
extern "C" int cleanup_exit_lvalue(bool cond) {
  int &r = (A(1), ({ if (cond) return 0; (void)0; }), getref());
  return r;
}

struct ByVal { int x[3]; };
extern "C" int cleanup_exit_lvalue_byval(bool cond, ByVal arg) {
  ByVal &r = (A(1), ({ if (cond) return 0; (void)ByVal(); }), arg);
  return r.x[0];
}

extern "C" int cleanup_exit_lvalue_local(bool cond) {
  int local = 42;
  int &r = (A(1), ({ if (cond) return 0; (void)0; }), local);
  return r;
}

_Complex float bar_complex(A, int);
extern "C" int cleanup_exit_complex(bool b) {
  _Complex float v = bar_complex(A(1), ({ if (b) return 42; 13; }));
  return (float)v;
}


extern "C" void then(int);

void volatile_load() {
  volatile int n;

  ({n;});

  then(1);

  ({goto lab; lab: n;});

  then(2);

  ({[[gsl::suppress("foo")]] n;});

  then(3);

  ({if (true) n;});

}

template<typename T>
void volatile_load_template() {
  volatile T n;

  ({n;});

  then(1);

  ({goto lab; lab: n;});

  then(2);

  ({[[gsl::suppress("foo")]] n;});

  then(3);

  ({if (true) n;});

}
template void volatile_load_template<int>();
