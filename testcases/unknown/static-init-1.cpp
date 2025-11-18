// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);

static int count;

int func2(int c) { return printf("loading the func2(%d)\n", c); };
int func1(int c) { return printf("loading the func1(%d)\n", c); }

static int loader_1 = func1(++count);

int loader_2 = func2(++count);

static int loader_3 = func1(++count);

int main() {}

int loader_4 = func2(++count);
static int loader_5 = func1(++count);
int loader_6 = func2(++count);

