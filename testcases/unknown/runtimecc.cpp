// RUN: %driver -cc1 %isys %s -fexceptions -fcxx-exceptions %target -o %t%output-suffix && %filecheck



namespace test0 {
  struct A {
    double d;
    A();
    ~A();
  };

  A global;
}


namespace test1 {
  void test() {
    throw 0;
  }

}





