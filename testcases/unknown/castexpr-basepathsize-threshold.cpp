// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck



template <typename a, a b(unsigned), int c, unsigned...>
struct d : d<a, b, c - 1> {};
template <typename a, a b(unsigned), unsigned... e>
struct d<a, b, 0, e...> {
  a f[0];
};
struct g {
  static g h(unsigned);
};
struct i {
  void j() const;
  d<g, g::h, (1U << 10U) - 2U> f;
};
void i::j() const {
  const void *k{f.f};
  (void)k;
}
