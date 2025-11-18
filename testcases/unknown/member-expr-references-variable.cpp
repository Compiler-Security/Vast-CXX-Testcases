// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct Agg { const char * x; const char * y; constexpr Agg() : x(0), y(0) {} };

struct Struct {
   constexpr static const char *name = "foo";

   constexpr static __complex float complexValue = 42.0;

   static constexpr const Agg &agg = Agg();

   Struct();
   Struct(int x);
};

void use(int n, const char *c);

Struct *getPtr();


void scalarStaticVariableInMemberExpr(Struct *ptr, Struct &ref) {
  use(1, Struct::name);
  Struct s;
  use(2, s.name);
  use(3, ptr->name);
  use(4, ref.name);
  use(5, Struct(2).name);
  use(6, getPtr()->name);
}

void use(int n, __complex float v);

void complexStaticVariableInMemberExpr(Struct *ptr, Struct &ref) {
  use(1, Struct::complexValue);
  Struct s;
  use(2, s.complexValue);
  use(3, ptr->complexValue);
  use(4, ref.complexValue);
  use(5, Struct(2).complexValue);
  use(6, getPtr()->complexValue);
}

void aggregateRefInMemberExpr(Struct *ptr, Struct &ref) {
  use(1, Struct::agg.x);
  Struct s;
  use(2, s.agg.x);
  use(3, ptr->agg.x);
  use(4, ref.agg.x);
}
