// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -O %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -fno-strict-return %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -fno-strict-return -Wno-return-type %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -fno-strict-return -O %s %target -o %t%output-suffix && %filecheck

int no_return() {




}

enum Enum {
  A, B
};

int returnNotViableDontOptimize(Enum e) {
  switch (e) {
  case A: return 1;
  case B: return 2;
  }

}

struct Trivial {
  int x;
};

Trivial trivial() {

}

struct NonTrivialCopy {
  NonTrivialCopy(const NonTrivialCopy &);
};

NonTrivialCopy nonTrivialCopy() {
}

struct NonTrivialDefaultConstructor {
  int x;

  NonTrivialDefaultConstructor() { }
};

NonTrivialDefaultConstructor nonTrivialDefaultConstructor() {
}


struct NonTrivialDestructor {
  ~NonTrivialDestructor();
};

NonTrivialDestructor nonTrivialDestructor() {
}

void lambdaTest() {
  auto lambda1 = []() -> int {
  };
  lambda1();


}
