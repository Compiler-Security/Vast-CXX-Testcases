// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct Alpha {
  virtual void bravo(...);
};
struct Charlie {
  virtual ~Charlie() {}
};
struct CharlieImpl : Charlie, Alpha {
  void bravo(...) {}
} delta;

