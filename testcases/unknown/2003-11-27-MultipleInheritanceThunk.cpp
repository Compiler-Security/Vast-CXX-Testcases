// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-rtti %s %target -o %t%output-suffix && %filecheck


struct CallSite {
  int X;

  CallSite(const CallSite &CS);
};

struct AliasAnalysis {
  int TD;

  virtual int getModRefInfo(CallSite CS);
};


struct Pass {
  int X;
  virtual int foo();
};

struct AliasAnalysisCounter : public Pass, public AliasAnalysis {
  int getModRefInfo(CallSite CS) {
    return 0;
  }
};

AliasAnalysisCounter AAC;
