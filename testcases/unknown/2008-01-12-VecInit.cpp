// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
typedef int __attribute__((vector_size(16))) v;
v vt = {1, 2, 3, 4};
