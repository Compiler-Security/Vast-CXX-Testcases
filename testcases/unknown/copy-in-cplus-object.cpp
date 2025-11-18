// RUN: %driver -cc1 %isys %s -fblocks %target -o %t%output-suffix && %filecheck

struct S {
  S(const char *);
  ~S();
};

struct TestObject
{
	TestObject(const TestObject& inObj, int def = 100,  const S &Silly = "silly");
	TestObject();
	~TestObject();
	TestObject& operator=(const TestObject& inObj);
	int version() const;

};

void testRoutine() {
    TestObject one;
    // int (^V)() = ^{ return one.version(); };
}

