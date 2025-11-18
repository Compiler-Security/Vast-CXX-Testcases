// RUN: %driver -cc1 %isys -std=c++1z -Werror %s %target -o %t%output-suffix && %filecheck


namespace std {
enum byte : unsigned char {};
}

extern "C" void test0(std::byte *sb, int *i) {
  *sb = std::byte{0};

  *i = 1;
}

enum byte : unsigned char {};
namespace my {
enum byte : unsigned char {};
namespace std {
enum byte : unsigned char {};
} // namespace std
} // namespace my


extern "C" void test1(::byte *b, ::my::byte *mb, ::my::std::byte *msb) {
  *b = ::byte{0};
  *mb = ::my::byte{0};
  *msb = ::my::std::byte{0};
}

