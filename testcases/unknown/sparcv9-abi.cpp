// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct pod {
  int a, b;
};

void f0();
void f1(struct pod);

struct notpod {
  int a, b;
  ~notpod() { f0(); }
};

void f2(struct notpod);

void caller()
{
  pod p1;
  notpod p2;
  f1(p1);
  f2(p2);
}
