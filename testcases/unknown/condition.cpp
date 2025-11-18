// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
void *f();

template <typename T> T* g() {
 if (T* t = f())
   return t;

 return 0;
}

void h() {
 void *a = g<void>();
}

struct X {
  X();
  X(const X&);
  ~X();
  operator bool();
};

struct Y {
  Y();
  ~Y();
};

X getX();

void if_destruct(int z) {
  if (X x = X()) {
    z = 18;
  }
  z = 17;

  if (X x = X())
    Y y;

  if (getX()) { }

}

struct ConvertibleToInt {
  ConvertibleToInt();
  ~ConvertibleToInt();
  operator int();
};

ConvertibleToInt getConvToInt();

void switch_destruct(int z) {
  switch (ConvertibleToInt conv = ConvertibleToInt()) {
  case 0:
    break;

  default:
    z = 19;
    break;
  }
  z = 20;

  switch(getConvToInt()) {
  case 0:
    break;
  }
  z = 27;
}

int foo();

void while_destruct(int z) {
  while (X x = X()) {


    z = 21;

  }

  z = 22;

  while(getX()) { }

  z = 25;

}

void for_destruct(int z) {

  for(Y y = Y(); X x = X(); ++z) {


    z = 23;




  }

  z = 24;




  int i = 0;
  for(; getX(); getX(), ++i) { }

  z = 26;

}

void do_destruct(int z) {
  do {
    z = 77;
  } while (getX());
  z = 99;
}

int f(X); 

template<typename T>
int instantiated(T x) { 
  int result;

  if (f(x)) { result = 2; } else { result = 3; }

  while (f(x)) { result = 4; }

  for (; f(x); f(x), result = 5) {
    result = 6;
  }

  switch (f(x)) {
  case 0: 
    result = 7;
    break;

  case 1:
    result = 8;
  }

  do {
    result = 9;
  } while (f(x));

  do {
    result = 10;
  } while (X(x));

  return result;
}

template int instantiated(X);
