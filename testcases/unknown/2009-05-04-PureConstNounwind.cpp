// RUN: %driver -cc1 %isys -fexceptions %s %target -o %t%output-suffix && %filecheck
int c(void) __attribute__((const));
int p(void) __attribute__((pure));
int t(void);

int f(void) {
  return c() + p() + t();
}


