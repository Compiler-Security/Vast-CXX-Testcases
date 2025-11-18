// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


int *[[clang::annotate_type("foo")]] f(int *[[clang::annotate_type("foo")]],
                                       int [[clang::annotate_type("foo")]]) {
  return nullptr;
}

template <class T> struct S {};

S<int *[[clang::annotate_type("foo")]]>
g(S<int *[[clang::annotate_type("foo")]]>) {
  return {};
}
