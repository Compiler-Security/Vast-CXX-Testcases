// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s -discard-value-names %target -o %t%output-suffix && %filecheck

extern "C" void branch();

bool test(bool pred) {

  if (pred) {

    branch();
  }


  return pred;
}
