// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck



__attribute__((visibility("default"))) thread_local int default_tls;
__attribute__((visibility("hidden"))) thread_local int hidden_tls;
