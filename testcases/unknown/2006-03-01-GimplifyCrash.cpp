// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct PrefMapElem {
  virtual ~PrefMapElem();
  unsigned int fPrefId;
};

int foo() {
  PrefMapElem* fMap;
  if (fMap[0].fPrefId == 1)
    return 1;

  return 0;
}
