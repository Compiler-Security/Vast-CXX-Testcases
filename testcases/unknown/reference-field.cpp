// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern struct x {char& x,y;}y;
int b();      
int a() { if (!&y.x) b(); }

