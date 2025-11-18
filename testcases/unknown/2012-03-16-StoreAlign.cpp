// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Length {
  Length(double v) {
    m_floatValue = static_cast<float>(v);
  }

  bool operator==(const Length& o) const {
    return getFloatValue() == o.getFloatValue();
  }
  bool operator!=(const Length& o) const { return !(*this == o); }
private:
  float getFloatValue() const {
    return m_floatValue;
  }
  float m_floatValue;
};


struct Foo {
  static Length inchLength(double inch);
  static bool getPageSizeFromName(const Length &A) {
    static const Length legalWidth = inchLength(8.5);
    if (A != legalWidth) return true;
    return false;
  }
};


bool bar(Length &b) {
  Foo f;
  return f.getPageSizeFromName(b);
}
