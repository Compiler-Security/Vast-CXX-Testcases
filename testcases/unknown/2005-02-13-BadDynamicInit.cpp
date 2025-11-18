// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct Data {
  unsigned *data;
  unsigned array[1];
};

Data shared_null = { shared_null.array };
