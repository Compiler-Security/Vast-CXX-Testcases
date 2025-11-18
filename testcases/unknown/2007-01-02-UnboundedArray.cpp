// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct Object {
  char buffer[];
};

int main(int argc, char** argv) {
  new Object;
  return 0;
}
