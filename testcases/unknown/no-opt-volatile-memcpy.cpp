// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct s {
  char filler [128];
  volatile int x;
};

struct s gs;

void foo (void) {
  struct s ls;
  ls = ls;
  gs = gs;
  ls = gs;
}


struct s1 {
  struct s y;
};

struct s1 s;

void fee (void) {
  s = s;
  s.y = gs;
}

struct d : s1 {
};

d gd;

void gorf(void) {
  gd = gd;
}
