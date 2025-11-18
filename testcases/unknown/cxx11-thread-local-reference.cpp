// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

int &f();

thread_local int &r = f();


int &g() { return r; }





