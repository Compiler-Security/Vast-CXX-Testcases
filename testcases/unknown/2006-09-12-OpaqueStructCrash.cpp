// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-rtti %s %target -o %t%output-suffix && %filecheck

struct A {
   virtual ~A();
};

template <typename Ty>
struct B : public A {
   ~B () { delete [] val; }
private:
     Ty* val;
};

template <typename Ty>
struct C : public A {
   C ();
   ~C ();
};

template <typename Ty>
struct D : public A {
     D () {}
   private:
     B<C<Ty> > blocks;
};

template class D<double>;
