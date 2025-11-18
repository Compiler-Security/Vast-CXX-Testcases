// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct fake_tuple;
struct connection {
    void bar(fake_tuple);
};
void (connection::*a)(fake_tuple) = &connection::bar;
void f() {
  void (connection::*b)(fake_tuple) = &connection::bar;
}
