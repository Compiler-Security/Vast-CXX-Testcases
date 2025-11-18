// RUN: %driver -cc1 %isys -mconstructor-aliases %s %target -o %t%output-suffix && %filecheck

struct Base { virtual ~Base(); };
struct Derived : Base {
  virtual ~Derived();
  static Derived inst;
};

Base::~Base(){}
Derived::~Derived(){}
Derived Derived::inst;


