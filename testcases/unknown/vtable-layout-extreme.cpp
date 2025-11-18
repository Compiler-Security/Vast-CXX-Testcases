// RUN: %driver -cc1 %isys %s -fdump-vtable-layouts %target -o %t%output-suffix && %filecheck


namespace Test1 {

class C0
{
};
class C1
 :  virtual public C0
{
  int k0;
};
class C2
 :  public C0
 ,  virtual public C1
{
  int k0;
};
class C3
 :  virtual public C0
 ,  virtual public C1
 ,  public C2
{
  int k0;
  int k1;
  int k2;
  int k3;
};
class C4
 :  public C2
 ,  virtual public C3
 ,  public C0
{
  int k0;
};
class C5
 :  public C0
 ,  virtual public C4
 ,  public C2
 ,  public C1
 ,  virtual public C3
{
  int k0;
};
class C6
 :  virtual public C3
 ,  public C0
 ,  public C5
 ,  public C4
 ,  public C1
{
  int k0;
};
class C7
 :  virtual public C5
 ,  virtual public C6
 ,  virtual public C3
 ,  public C4
 ,  virtual public C2
{
  int k0;
  int k1;
};
class C8
 :  public C7
 ,  public C5
 ,  public C3
 ,  virtual public C4
 ,  public C1
 ,  public C2
{
  int k0;
  int k1;
};

class C9
 :  virtual public C6
 ,  public C2
 ,  public C4
 ,  virtual public C8
{
  int k0;
  int k1;
  int k2;
  int k3;
  virtual void f();
};
void C9::f() { }

}
