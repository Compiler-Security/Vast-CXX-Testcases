// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
    bool m_sorted : 1;
};
void func1(bool b, A& a1)
{
    if ((a1.m_sorted = b)) {}
}
