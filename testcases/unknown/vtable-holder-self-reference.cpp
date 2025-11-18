// RUN: %driver -cc1 %isys -dwarf-version=2 -x c++ %s %target -o %t%output-suffix && %filecheck

void foo() {
  struct V {
    int vi;
  };
  struct B : virtual V {};
  B b;
}
