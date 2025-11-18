// RUN: %driver -cc1 %isys -I%S %s -std=c++11 %target -o %t%output-suffix && %filecheck
#include <typeinfo>

namespace Test1 {

struct Item {
  const std::type_info &ti;
  const char *name;
  void *(*make)();
};

template<typename T> void *make_impl() { return new T; }
template<typename T> constexpr Item item(const char *name) {
  return { typeid(T), name, make_impl<T> };
}

struct A { virtual ~A(); };
struct B : virtual A {};
struct C { int n; };

extern constexpr Item items[] = {
  item<A>("A"), item<B>("B"), item<C>("C"), item<int>("int")
};

constexpr auto &x = items[0].ti;

constexpr auto &y = typeid(B{});

}
