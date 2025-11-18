// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct K
{
  K();
  K(const K &);
  ~K();
  void PrintNumK();
};

template<typename T>
struct C
{
  void Go() { needs_guard.PrintNumK(); }
  static K needs_guard;
};

template<typename T> K C<T>::needs_guard;

void F()
{
  C<int>().Go();
}

