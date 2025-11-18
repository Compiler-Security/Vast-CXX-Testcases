// RUN: %driver -cc1 %isys -std=c++03 %s %target -o %t%output-suffix && %filecheck

class S {
  char *ptr;
  unsigned int len;
};

class T {
  S left;
  S right;

public:
  T(const char s[]);
  T(S);

  T concat(const T &Suffix) const;
  const char * str() const;
};

const char * f(S s)
{

  return T("[").concat(T(s)).str();
}

