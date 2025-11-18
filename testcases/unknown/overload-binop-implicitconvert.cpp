// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
class T
{};

void print(const char *t);

T& operator<< (T& t,const char* c)
{
  print(c);
  return t;
}


int main()
{
  T t;
  print("foo");
  t<<"foo";
  
  return 0;
}
  
