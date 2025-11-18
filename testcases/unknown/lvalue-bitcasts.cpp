// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct X { int i; float f; };
struct Y { X x; };

void reinterpret_cast_test(int &ir, float &fr, X &xr) {
  ir = reinterpret_cast<int&>(fr);
  ir = reinterpret_cast<int&>(xr);
  fr = reinterpret_cast<float&>(ir);
  fr = reinterpret_cast<float&>(xr);
  xr = reinterpret_cast<X&>(ir);
  xr = reinterpret_cast<X&>(fr);
  _Complex float cf;
  _Complex float &cfr = cf;
  cfr = reinterpret_cast<_Complex float&>(ir);
  cfr = reinterpret_cast<_Complex float&>(fr);
  cfr = reinterpret_cast<_Complex float&>(xr);
}

void c_cast(int &ir, float &fr, X &xr) {
  ir = (int&)fr;
  ir = (int&)xr;
  fr = (float&)ir;
  fr = (float&)xr;
  xr = (X&)ir;
  xr = (X&)fr;
  _Complex float cf;
  _Complex float &cfr = cf;
  cfr = (_Complex float&)ir;
  cfr = (_Complex float&)fr;
  cfr = (_Complex float&)xr;
}

void functional_cast(int &ir, float &fr, X &xr) {
  typedef int &intref;
  typedef float &floatref;
  typedef X &Xref;
  ir = intref(fr);
  ir = intref(xr);
  fr = floatref(ir);
  fr = floatref(xr);
  xr = Xref(ir);
  xr = Xref(fr);
  typedef _Complex float &complex_float_ref;
  _Complex float cf;
  _Complex float &cfr = cf;
  cfr = complex_float_ref(ir);
  cfr = complex_float_ref(fr);
  cfr = complex_float_ref(xr);
}

namespace PR6437 {
  struct in_addr {};
  void copy( const struct in_addr &new_addr ) {
    int addr = (int&)new_addr;
  }
}

namespace PR7593 {
  void foo(double &X, char *A) {
    X = reinterpret_cast<double&>(A[4]);
  }
}

namespace PR7344 {
  void serialize_annotatable_id( void*& id )
  {
    unsigned long l_id = (unsigned long&)id;
  }
}
