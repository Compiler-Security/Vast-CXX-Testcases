// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

template <typename T>
struct HasStaticInit {
static const int index;
};
extern "C"
int the_count = 0;
template <typename T>
const int HasStaticInit<T>::index = the_count++;

template <typename T> int func_tmpl1() { return HasStaticInit<T>::index; }
template <typename T> int func_tmpl2() { return HasStaticInit<T>::index; }
template <typename T> int func_tmpl3() { return HasStaticInit<T>::index; }
void useit() {
  func_tmpl1<int>();
  func_tmpl2<int>();
  func_tmpl3<int>();
}

template struct HasStaticInit<int>;


