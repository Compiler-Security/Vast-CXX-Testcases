// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

union sigval { };
union sigval Test1;

union NonPODUnion { ~NonPODUnion(); };
union NonPODUnion Test2;
