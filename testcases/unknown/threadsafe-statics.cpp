// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -fno-threadsafe-statics %target -o %t%output-suffix && %filecheck

int f();


void g() { 
  static int a = f();
}




