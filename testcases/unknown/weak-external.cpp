// RUN: %driver -cc1 %isys -fcxx-exceptions -fexceptions %s %target -o %t%output-suffix && %filecheck



#define _LIBCPP_EXCEPTION_ABI __attribute__ ((__visibility__("default")))
#define _LIBCPP_INLINE_VISIBILITY __attribute__ ((__visibility__("hidden"), __always_inline__))
#define _LIBCPP_VISIBLE __attribute__ ((__visibility__("default")))
#if (__has_feature(cxx_noexcept))
#  define _NOEXCEPT noexcept
#  define _NOEXCEPT_(x) noexcept(x)
#else
#  define _NOEXCEPT throw()
#  define _NOEXCEPT_(x)
#endif

namespace std  // purposefully not using versioning namespace
{

template<class charT> struct char_traits;
template<class T>     class allocator;
template <class _CharT,
          class _Traits = char_traits<_CharT>,
          class _Allocator = allocator<_CharT> >
    class _LIBCPP_VISIBLE basic_string;
typedef basic_string<char, char_traits<char>, allocator<char> > string;

class _LIBCPP_EXCEPTION_ABI exception
{
public:
    _LIBCPP_INLINE_VISIBILITY exception() _NOEXCEPT {}
    virtual ~exception() _NOEXCEPT;
    virtual const char* what() const _NOEXCEPT;
};

class _LIBCPP_EXCEPTION_ABI runtime_error
    : public exception
{
private:
    void* __imp_;
public:
    explicit runtime_error(const string&);
    explicit runtime_error(const char*);

    runtime_error(const runtime_error&) _NOEXCEPT;
    runtime_error& operator=(const runtime_error&) _NOEXCEPT;

    virtual ~runtime_error() _NOEXCEPT;

    virtual const char* what() const _NOEXCEPT;
};

}

void dummysymbol() {
  throw(std::runtime_error("string"));
}

namespace not_weak_on_first {
  int func();
  int func() __attribute__ ((weak));

  typedef int (*FuncT)();

  extern const FuncT table[] = {
      func,
  };
}

namespace constant_eval {
  [[gnu::weak]] extern int a;
  bool has_a1 = &a;
  bool has_a2 = &a != nullptr;

  struct X {
    [[gnu::weak]] void f();
  };
  bool has_f1 = &X::f;
  bool has_f2 = &X::f != nullptr;
}
