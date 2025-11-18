// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck


struct Spacer { int x; };
struct A { double array[2]; };
struct B : Spacer, A { };

B &getB();

A &&getA() { return static_cast<A&&>(getB()); }

int &getIntLValue();
int &&getIntXValue();
int getIntPRValue();

int &&f0() { return static_cast<int&&>(getIntLValue()); }

int &&f1() { return static_cast<int&&>(getIntXValue()); }

int &&f2() { return static_cast<int&&>(getIntPRValue()); }

bool ok;

class C
{
   int* state_;

   C(const C&) = delete;
   C& operator=(const C&) = delete;
public:
  C(int state) : state_(new int(state)) { }
  
  C(C&& a) {
    state_ = a.state_; 
    a.state_ = 0;
  }

  ~C() {
    delete state_; 
    state_ = 0;
  }
};

C test();

void elide_copy_init() {
  ok = false;
  C a = test();
}

C test_move_return() {
  C a1(3);
  C a2(4);
  if (ok)
    return a1;
  return a2;
}

namespace test1 {
  int &&move(int&);

  struct A { A(int); };
  struct B {
    A a;
    B(int i);
  };

  B::B(int i) : a(move(i)) {}
}

struct MoveConvertible {
  operator int&& () const;
};
void moveConstruct() {
  (void)(int)MoveConvertible();
}
