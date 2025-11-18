// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

__attribute__((target("default"))) static int static_target() {
  return 0;
}
__attribute__((target("arch=sandybridge"))) static int static_target() {
  return 1;
}

__attribute__((cpu_dispatch(atom, generic))) static int static_dispatch() {}

namespace {
int __attribute__((target("default"))) anon_target() {
  return 0;
}
int __attribute__((target("arch=sandybridge"))) anon_target() {
  return 1;
}
__attribute__((cpu_dispatch(atom, generic))) static int anon_dispatch() {}
}



int usage() {
  return static_target() + anon_target() + static_dispatch() + anon_dispatch();
}



