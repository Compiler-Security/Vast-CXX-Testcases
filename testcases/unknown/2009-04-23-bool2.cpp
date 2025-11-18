// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct F {
  bool b1 : 1;
  bool b2 : 7;
};

int main()
{
  F f = { true, true };

  if (int (f.b1) != 1)
    return 1;
}
