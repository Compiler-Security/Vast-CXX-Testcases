// RUN: %driver -cc1 %isys -w %s %target -o %t%output-suffix && %filecheck

extern "C" {
  struct statvfs64 {
    int f;
  };
#pragma redefine_extname statvfs64 statvfs
  int statvfs64(struct statvfs64 *);
}

void some_func() {
  struct statvfs64 st;
  statvfs64(&st);
}

#pragma redefine_extname foo bar
int f() {
  int foo = 0;
  return foo;
}
extern "C" {
  int foo() { return 1; }
}

#pragma redefine_extname foo_cpp bar_cpp
extern int foo_cpp() { return 1; }

