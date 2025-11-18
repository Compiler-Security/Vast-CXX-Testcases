// RUN: %driver -cc1 %isys -std=c++1y %s %target -o %t%output-suffix && %filecheck



struct A {
  ~A();
};

thread_local A a;

extern thread_local int ext;
int &get_ext() { return ext; }

template <typename T>
thread_local int vt = 5;

int get_vt() { return vt<int>; }

inline int &inl() {
  thread_local int loc;
  return loc;
}
int &use_inl() { return inl(); }

template int vt<void>;
int &get_vt_void() { return vt<void>; }
