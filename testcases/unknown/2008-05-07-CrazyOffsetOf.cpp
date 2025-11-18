// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct bork {
  struct bork *next_local;
  char * query;
};
int offset =  (char *) &(((struct bork *) 0x10)->query) - (char *) 0x10;
