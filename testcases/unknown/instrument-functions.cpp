// RUN: %driver -cc1 %isys %s -finstrument-functions %target -o %t%output-suffix && %filecheck

int test1(int x) {
  return x;
}

int test2(int) __attribute__((no_instrument_function));
int test2(int x) {
  return x;
}




namespace rdar9445102 {
  class Rdar9445102 {
    public:
      Rdar9445102();
  };
}
static rdar9445102::Rdar9445102 s_rdar9445102Initializer;

