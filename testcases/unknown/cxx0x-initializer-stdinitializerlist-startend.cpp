// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

namespace std {
  typedef decltype(sizeof(int)) size_t;

  template <class _E>
  class initializer_list
  {
    const _E* __begin_;
    const _E* __end_;

    initializer_list(const _E* __b, const _E* __e)
      : __begin_(__b),
        __end_(__e)
    {}

  public:
    typedef _E        value_type;
    typedef const _E& reference;
    typedef const _E& const_reference;
    typedef size_t    size_type;

    typedef const _E* iterator;
    typedef const _E* const_iterator;

    initializer_list() : __begin_(nullptr), __end_(nullptr) {}

    size_t    size()  const {return __end_ - __begin_;}
    const _E* begin() const {return __begin_;}
    const _E* end()   const {return __end_;}
  };
}

std::initializer_list<int> globalInitList1 = {1, 2, 3};

void fn1(int i) {
  std::initializer_list<int> intlist{1, 2, i};
}

struct destroyme1 {
  ~destroyme1();
};
struct destroyme2 {
  ~destroyme2();
};


void fn2() {
  void target(std::initializer_list<destroyme1>);
  target({ destroyme1(), destroyme1() });
  destroyme2 dm2;
}

void fn3() {
  auto list = { destroyme1(), destroyme1() };
  destroyme2 dm2;
}
