// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


namespace nm {
  struct str {
    friend void foo(int arg = 0) {};
  };
}
