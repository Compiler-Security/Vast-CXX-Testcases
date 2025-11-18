// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Global { Global(); };
template<typename T> struct X { X() {} };


namespace {
  struct Anon { Anon() {} };

  Global anon0;
}

Anon anon1;

X<Anon> anon2;

char const * const xyzzy = "Hello, world!";
extern char const * const xyzzy;

char const * const *test1()
{
    return &xyzzy;
}

static char const * const static_xyzzy = "Hello, world!";
extern char const * const static_xyzzy;

char const * const *test2()
{
    return &static_xyzzy;
}

static char const * static_nonconst_xyzzy = "Hello, world!";
extern char const * static_nonconst_xyzzy;

char const * *test3()
{
    return &static_nonconst_xyzzy;
}


char const * extern_nonconst_xyzzy = "Hello, world!";
extern char const * extern_nonconst_xyzzy;

char const * *test4()
{
    return &extern_nonconst_xyzzy;
}

template <typename T> class klass {
    virtual void f();
};
namespace { struct S; }
void foo () { klass<S> x; }
