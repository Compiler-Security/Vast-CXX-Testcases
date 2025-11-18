// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct Foo {
  int x;
  Foo();
  ~Foo();
};

void inalloca(Foo x, Foo y);

extern "C" void pr25102() {
  inalloca(Foo(), ({
             goto out;
             Foo();
           }));
out:;
}


bool cond();
extern "C" void seqAbort() {
  inalloca(Foo(), ({
             if (cond())
               goto out;
             Foo();
           }));
out:;
}

