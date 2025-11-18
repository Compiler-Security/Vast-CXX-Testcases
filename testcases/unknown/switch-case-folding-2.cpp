// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern int printf(const char*, ...);

int test(int val){
 switch (val) {
 case 4:
   do {
     switch (6) {
       case 6: do { case 5: printf("bad\n"); } while (0);
     };
   } while (0);
 }
 return 0;
}

int main(void) {
 return test(5);
}

void other_test() {
  switch(0) {
  case 0:
    do {
    default:;
    } while(0);
  }
}

struct X { X(); ~X(); };

void dont_call();
void foo();

void nested_scopes() {
  switch (1) {
  case 0:
    dont_call();
    break;

  default:
    { X x; foo(); }

    { X x; foo(); }

    { X x; foo(); }
    break;
  }
}

void scope_fallthrough() {
  switch (1) {
    { default: X x; }
    foo();
    break;
  }
}

void hidden_break(bool b) {
  switch (1) {
  default:
    if (b)
      break;
    foo();
    break;
  }
}

int hidden_var() {
  switch (1) {
  case 0: int n;
  default: n = 0; return n;
  }
}

void case_in_label() {
  switch (1) case 1: foo: case 0: goto foo;
}
