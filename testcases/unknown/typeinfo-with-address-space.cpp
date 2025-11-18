// RUN: %driver -cc1 %isys -I%S %s %target -o %t%output-suffix && %filecheck
#include <typeinfo>

class A {
    virtual void f() = 0;
};

class B : A {
    void f() override;
};


unsigned long Fn(B& b) {
    if (typeid(std::type_info) == typeid(b))
        return 42;
    if (typeid(int) != typeid(b))
        return 1712;
    if (typeid(A).name() == typeid(b).name())
        return 0;
    if (typeid(b).before(typeid(float)))
        return 1;
    return typeid(b).hash_code();
}
