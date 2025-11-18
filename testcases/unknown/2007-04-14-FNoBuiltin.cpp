// RUN: %driver -cc1 %isys %s -fno-builtin %target -o %t%output-suffix && %filecheck

extern "C" int printf(const char*, ...);
void foo(const char *msg) {
	printf("%s\n",msg);
}
