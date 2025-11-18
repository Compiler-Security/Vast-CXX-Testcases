// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct foo {
  char x:8;
  signed int y:24;
};
int bar(struct foo p, int x) {
  x = (p.y > x ? x : p.y);
  return x;
}
