// RUN: %driver -cc1 %isys -DUNWIND -fcxx-exceptions -fexceptions %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fcxx-exceptions -fexceptions %s %target -o %t%output-suffix && %filecheck

extern "C" void printf(const char *fmt, ...);

struct DropBomb {
  bool defused = false;

  ~DropBomb() {
    if (defused) {
      return;
    }
    printf("Boom!\n");
  }
};

extern "C" void trap() {
  throw "Trap";
}

extern "C" void test() {
  DropBomb bomb;
#ifdef UNWIND
  asm volatile("call trap" ::
                   : "unwind");
#else
  asm volatile("call trap" ::
                   :);
#endif
  bomb.defused = true;
}
