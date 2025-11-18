// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


class foo {
  virtual void baz();
};
struct __attribute__((__visibility__("hidden"))) bar : public foo {};
bar zed;
