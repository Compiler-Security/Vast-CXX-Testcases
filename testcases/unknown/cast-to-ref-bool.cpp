// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int main(int argc, char **argv) {
  bool b = (bool &)argv[argc][1];
  return b;
}
