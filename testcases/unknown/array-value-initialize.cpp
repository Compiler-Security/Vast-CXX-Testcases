// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);

struct S {
  double filler;
};

struct Foo {
        Foo(void) : bar_(), dbar_(), sbar_() { 
	  for (int i = 0; i < 5; i++) {
	    printf("bar_[%d] = %d\n", i, bar_[i]);
	    printf("dbar_[%d] = %f\n", i, dbar_[i]);
	    printf("sbar_[%d].filler = %f\n", i, sbar_[i].filler);
	  }
        } 

        int bar_[5];
        double dbar_[5];
        S sbar_[5];
};

int test1(void) {
        Foo a;
}



struct Unit
{
  Unit() {}
  Unit(const Unit& v)  {}
};


struct Stuff
{
  Unit leafPos[1];
};


int main()
{
  
  Stuff a;
  Stuff b = a;
  
  return 0;
}
