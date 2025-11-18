// RUN: %driver -cc1 %isys -std=c++14 -fblocks %s %target -o %t%output-suffix && %filecheck


void testRemap() {
  const char *file = __builtin_FILE();
}

#line 8 "builtin-source-location.cpp"

namespace std {
class source_location {
public:
  static constexpr source_location current(const void *__p = __builtin_source_location()) noexcept {
    source_location __loc;
    __loc.__m_impl = static_cast<const __impl *>(__p);
    return __loc;
  }
  static source_location bad_current(const void *__p = __builtin_source_location()) noexcept {
    return current(__p);
  }
  constexpr source_location() = default;
  constexpr source_location(source_location const &) = default;
  constexpr unsigned int line() const noexcept { return __m_impl->_M_line; }
  constexpr unsigned int column() const noexcept { return __m_impl->_M_column; }
  constexpr const char *file() const noexcept { return __m_impl->_M_file_name; }
  constexpr const char *function() const noexcept { return __m_impl->_M_function_name; }

private:
  struct __impl {
    const char *_M_file_name;
    const char *_M_function_name;
    unsigned _M_line;
    unsigned _M_column;
  };
  const __impl *__m_impl = nullptr;
};
} // namespace std

using SL = std::source_location;

extern "C" int sink(...);

#line 1000 "test_const_init.cpp"
SL const_init_global = SL::current();


#line 1100 "test_runtime_init.cpp"
SL runtime_init_global = SL::bad_current();

#line 2000 "test_function.cpp"
extern "C" void test_function() {
#line 2100 "test_current.cpp"
  SL local = SL::current();
}

#line 3000 "TestInitClass.cpp"
struct TestInit {
  SL info = SL::current();
  SL arg_info;

#line 3100 "TestInitCtor.cpp"
  TestInit(SL arg_info = SL::current()) : arg_info(arg_info) {}
};

#line 3400 "GlobalInitVal.cpp"
TestInit GlobalInitVal;

extern "C" void test_init_function() {

#line 3500 "LocalInitVal.cpp"
  TestInit init_local;
  sink(init_local);
}

#line 4000 "ConstexprClass.cpp"
struct TestInitConstexpr {
  SL info = SL::current();
  SL arg_info;
#line 4200 "ConstexprCtor.cpp"
  constexpr TestInitConstexpr(SL arg_info = SL::current()) : arg_info(arg_info) {}
};

#line 4400 "ConstexprGlobal.cpp"
TestInitConstexpr ConstexprGlobal;

extern "C" void test_init_function_constexpr() {
#line 4600 "ConstexprLocal.cpp"
  TestInitConstexpr local_val;
}

#line 5000 "TestInitAgg.cpp"
struct TestInitAgg {
#line 5100 "i1.cpp"
  SL i1;
#line 5200 "i2.cpp"
  SL i2 = SL::current();
#line 5300 "TestInitAggEnd.cpp"
};

#line 5400 "GlobalAggDefault.cpp"
TestInitAgg GlobalAggDefault;

#line 5500 "test_agg_init_test.cpp"
extern "C" void test_agg_init() {



#line 5600 "BraceInitStart.cpp"
  TestInitAgg local_brace_init{
#line 5700 "BraceInitEnd.cpp"
  };


#line 5800 "EqualInitStart.cpp"
  TestInitAgg local_equal_init =
      {
#line 5900 "EqualInitEnd.cpp"
      };



#line 6000 "InitListStart.cpp"
  TestInitAgg local_list_init =
      {
#line 6100 "ListElem.cpp"
          {SL::current()}
#line 6200 "InitListEnd.cpp"
      };
}

#line 7000 "TestTemplate.cpp"
template <class Tp, int>
struct TestTemplate {
  Tp info = Tp::current();
  Tp arg_info;
#line 7100 "TestTemplateCtor.cpp"
  constexpr TestTemplate(Tp arg_info = Tp::current()) : arg_info(arg_info) {}
};

#line 7200 "test_template.cpp"
template <class T, int V>
void test_template() {

#line 7300 "local_templ.cpp"
  TestTemplate<T, V> local_templ;
}
#line 7400 "EndTestTemplate.cpp"
template void test_template<SL, 0>();
template void test_template<SL, 1>();
