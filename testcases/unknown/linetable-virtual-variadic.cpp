// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
class Base {
  virtual void VariadicFunction(...);
};

class Derived : public virtual Base {
  virtual void VariadicFunction(...);
};

void Derived::VariadicFunction(...) { }

