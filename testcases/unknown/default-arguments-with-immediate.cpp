// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck

consteval int immediate() { return 0;}
static int ext();
void f(int a = immediate() + ext());

void test_function() {
    f();
    f(0);
}


static constexpr int not_immediate();
struct A {
    int a = immediate() + not_immediate();
};

void test_member() {
    A defaulted;
    A provided{0};
}


int never_referenced() {return 42;};


namespace not_used {

struct A {
    int a = immediate() + never_referenced();
};
void f(int a = immediate() + never_referenced());

void g() {
    A a{0};
    f(0);
}

}

static int ext() {return 0;}
static constexpr int not_immediate() {return 0;}

