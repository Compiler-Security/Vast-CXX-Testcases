// RUN: %driver -cc1 %isys -fblocks %s -std=c++1y %target -o %t%output-suffix && %filecheck


namespace pr6769 {
struct X {
  static void f();
};

void X::f() {
  static int *i;
  {
    struct Y {
      static void g() {
        i = new int();
	*i = 100;
	(*i) = (*i) +1;
      }
    };
    (void)Y::g();
  }
  (void)i;
}
}

namespace pr7101 {
void foo() {
    static int n = 0;
    struct Helper {
        static void Execute() {
            n++;
        }
    };
    Helper::Execute();
}
}


namespace pr18020_lambda {
auto x = []() {
  static int l1 = 0;
  return [] { return l1; };
};
int f() { return x()(); }
}


namespace pr18020_constexpr {
auto x = []() {
  static int l1 = 0;
  return [] {
    static int *l2 = &l1;
    return *l2;
  };
};
int f() { return x()(); }
}


struct pr18020_class {
  auto operator()() {
    static int l1 = 0;
    struct U {
      int operator()() { return l1; }
    };
    return U();
  }
};
static pr18020_class x;
int pr18020_f() { return x()(); }


static auto deduced_return() {
  static int n = 42;
  struct S { int *operator()() { return &n; } };
  return S();
}
extern "C" int call_deduced_return_operator() {
  return *decltype(deduced_return())()();
}



// static auto block_deduced_return() {
//   auto (^b)() = ^() {
//     static int n = 42;
//     struct S { int *operator()() { return &n; } };
//     return S();
//   };
//   return b();
// }
// extern "C" int call_block_deduced_return() {
//   return *decltype(block_deduced_return())()();
// }



// inline auto static_local_label(void *p) {
//   if (p)
//     goto *p;
//   static void *q = &&label;
//   struct S { static void *get() { return q; } };
//   return S();
// label:
//   __builtin_abort();
// }
// void *global_label = decltype(static_local_label(0))::get();


auto global_lambda = []() {
  static int x = 42;
  struct S { static int *get() { return &x; } };
  return S();
};
extern "C" int use_global_lambda() {
  return *decltype(global_lambda())::get();
}

