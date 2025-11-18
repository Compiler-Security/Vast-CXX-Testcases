// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck



struct S_small {
  int a[8];
};

struct S_large {
  int a[9];
};

struct Combiner {
  S_large a, b;

  Combiner(S_large);
  Combiner f();
};

extern S_small foo_small();
extern S_large foo_large();
extern void bar_small(S_small*);
extern void bar_large(S_large*);

extern "C" {

void small_rvoed_unnamed_temporary_object() {

  foo_small();
  foo_small();
}

void large_rvoed_unnamed_temporary_object() {

  foo_large();
  foo_large();
}

void small_rvoed_named_temporary_object() {

  {
    S_small s = foo_small();
  }
  {
    S_small s = foo_small();
  }
}

void large_rvoed_named_temporary_object() {

  {
    S_large s = foo_large();
  }
  {
    S_large s = foo_large();
  }
}

void small_auto_object() {

  {
    S_small s;
    bar_small(&s);
  }
  {
    S_small s;
    bar_small(&s);
  }
}

void large_auto_object() {

  {
    S_large s;
    bar_large(&s);
  }
  {
    S_large s;
    bar_large(&s);
  }
}

int large_combiner_test(S_large s) {

  return Combiner(s).f().a.a[0];
}

}
