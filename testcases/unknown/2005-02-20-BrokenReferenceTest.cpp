// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

void test(unsigned char *b, int rb) {
  typedef unsigned char imgfoo[10][rb];
  imgfoo &br = *(imgfoo *)b;

  br[0][0] = 1;

  rb = br[0][0];
}
