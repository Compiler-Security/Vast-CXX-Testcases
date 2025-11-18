// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int x();
int y = x() & 0;
