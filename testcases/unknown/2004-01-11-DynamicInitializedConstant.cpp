// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


extern int X;
const int Y = X;
const int* foo() { return &Y; }
