// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

template<class T>
void thefunc();

template<class T>
inline void thefunc() {}

void test() {
  thefunc<int>();
}
