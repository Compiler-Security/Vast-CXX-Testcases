// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-delete-null-pointer-checks %s %target -o %t%output-suffix && %filecheck

struct Struct {
  int many;
  int member;
  int fields;
  void ReturnsVoid();
};

void TestReturnsVoid(Struct &s) {
  s.ReturnsVoid();

}

