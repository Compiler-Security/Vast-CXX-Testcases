// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace Test1 {

struct A {
  virtual void f();
  ~A();
};

A::~A() 
{
}

}

namespace Test2 {

struct A {
  virtual void f();
  ~A();
};

A::~A() {
  f();
}

}

namespace Test3 {

struct Field {
  ~Field() { }
};

struct A {
  virtual void f();
  ~A();

  Field field;
};

A::~A() {
  
}

}

namespace Test4 {


void f();

struct Field {
  ~Field() { f(); }
};

struct A {
  virtual void f();
  ~A();

  Field field;
};

A::~A()
{
}

}

namespace Test5 {


struct Field {
  ~Field();
};

struct A {
  virtual void f();
  ~A();

  Field field;
};

A::~A()
{
}

}

namespace Test6 {


struct NonTrivialDestructorBody {
  ~NonTrivialDestructorBody();
};

struct Field {
  NonTrivialDestructorBody nonTrivialDestructorBody;
};

struct A {
  virtual void f();
  ~A();

  Field field;
};

A::~A()
{
}

}

namespace Test7 {


struct NonTrivialDestructorBody {
  ~NonTrivialDestructorBody();
};

struct Field : NonTrivialDestructorBody { };

struct A {
  virtual void f();
  ~A();

  Field field;
};

A::~A()
{
}

}

namespace Test8 {


struct NonTrivialDestructorBody {
  ~NonTrivialDestructorBody();
};

struct Field : virtual NonTrivialDestructorBody { };

struct A {
  virtual void f();
  ~A();

  Field field;
};

A::~A()
{
}

}

namespace Test9 {

struct A { virtual ~A () { } };
struct B : virtual A {};
struct C : virtual B { 
  virtual ~C();
};
C::~C() {}

}
