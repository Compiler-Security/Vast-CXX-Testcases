// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Field {
  Field();
  ~Field();
};

struct Base {
  Base();
  ~Base();
};

struct A : Base {
  A();
  ~A();

  virtual void f();
  
  Field field;
};

A::A() { }

A::~A() { } 

struct B : Base {
  virtual void f();
  
  Field field;
};

void f() { B b; }




