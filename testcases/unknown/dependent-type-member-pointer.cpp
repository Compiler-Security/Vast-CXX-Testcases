// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

template <class scriptmemberptr> int InitMember(scriptmemberptr);

template <class> 
struct contentmap
{
  static void InitDataMap()
  { InitMember(&contentmap::SizeHolder); }
  int SizeHolder;
};

void ReadFrom( )
{
  contentmap<int>::InitDataMap();
}

