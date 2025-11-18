// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
class MO {

  union {       struct {       union {    int BA;       } Val;       int Offset;     } OffsetedInfo;   } Contents; 

};

class MO m;
