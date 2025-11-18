// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct Strongbad {
    Strongbad(const char *str );
    ~Strongbad();
    operator const char *() const;
};

void TheCheat () {
  Strongbad foo(0);
  Strongbad dirs[] = { Strongbad(0) + 1};
}
