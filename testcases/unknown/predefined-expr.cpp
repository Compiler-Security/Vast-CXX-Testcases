// RUN: %driver -cc1 %isys -std=c++11 -fblocks %s %target -o %t%output-suffix && %filecheck































int printf(const char * _Format, ...);

class ClassInTopLevelNamespace {
public:
  void topLevelNamespaceFunction() {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }
};

namespace {

  class ClassInAnonymousNamespace {
  public:
    void anonymousNamespaceFunction() {
      printf("__func__ %s\n", __func__);
      printf("__FUNCTION__ %s\n", __FUNCTION__);
      printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
    }
  };

} // end anonymous namespace

namespace NS {

template<typename T>
class ClassTemplate {
public:
  void classTemplateFunction() {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }
};

class Base {
public:
  static void staticFunction() {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  inline void (inlineFunction)() {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  virtual void virtualFunction() {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  void functionWithParameters(int, float*, Base* base) {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  Base *functionReturningClass() {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
    return 0;
  }

  void variadicFunction(int, ...) {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  void withTemplateParameter1(ClassTemplate<int>) {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  void withTemplateParameter2(ClassTemplate<Base *>) {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  ClassTemplate<int> functionReturingTemplate1() {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
    return ClassTemplate<int>();
  }

  ClassTemplate<Base *> functionReturingTemplate2() {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
    return ClassTemplate<Base *>();
  }

  template<typename T>
  void functionTemplate1(T t) {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  void constFunction() const {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  void volatileFunction() volatile {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }
  
  void constVolatileFunction() const volatile {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  void refQualifiedFunction() & {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  void refQualifiedFunction() && {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }
};

class Derived : public Base {
public:
  void virtualFunction() {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }
};

class Constructor {
public:
  Constructor() {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  Constructor(int) {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }

  Constructor(Base *) {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }
};

class Destructor {
public:
  ~Destructor() {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }
};

class ContainerForAnonymousRecords {
public:
  class {
  public:
    void anonymousClassFunction() {
      printf("__func__ %s\n", __func__);
      printf("__FUNCTION__ %s\n", __FUNCTION__);
      printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
    }
  } anonymousClass;

  struct {
    void anonymousStructFunction() {
      printf("__func__ %s\n", __func__);
      printf("__FUNCTION__ %s\n", __FUNCTION__);
      printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
    }
  } anonymousStruct;

  union {
    void anonymousUnionFunction() {
      printf("__func__ %s\n", __func__);
      printf("__FUNCTION__ %s\n", __FUNCTION__);
      printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
    }
  } anonymousUnion;
};

void localClass(int) {
  class LocalClass {
  public:
    void localClassFunction() {
      printf("__func__ %s\n", __func__);
      printf("__FUNCTION__ %s\n", __FUNCTION__);
      printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
    }
  };
  LocalClass lc;
  lc.localClassFunction();
}

extern void externFunction() {
  printf("__func__ %s\n", __func__);
  printf("__FUNCTION__ %s\n", __FUNCTION__);
  printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
}

} // end NS namespace

template <typename T, typename U>
void functionTemplateWithTwoParams(T, U)
{
  printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
}

template <typename T>
void functionTemplateWithoutParameterList()
{
  T t = T();

  printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
}

template <typename T>
T functionTemplateWithTemplateReturnType()
{
  printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);

  return T();
}

template <typename T>
T * functionTemplateWithCompoundTypes(T a[])
{
  printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);

  return 0;
}

template <typename T>
void functionTemplateExplicitSpecialization(T t)
{
  printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
}

template <>
void functionTemplateExplicitSpecialization<int>(int i)
{
  printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
}

template <typename, typename T>
void functionTemplateWithUnnamedTemplateParameter(T t)
{
  printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
}

template <typename T>
void functionTemplateWithLambda(T t)
{
  []() {
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  } ();
}

template <typename T>
void functionTemplateWithCapturedStmt(T t)
{
  // #pragma clang __debug captured
  // {
  //   printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  // }
}

template <typename T>
class OuterClass
{
public:
  class MiddleClass
  {
  public:
    template <typename U>
    class InnerClass
    {
    public:
      void memberFunction(T x, U y) const
      {
        printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
      }
    };
  };
};

template <typename T, template <typename> class Param = NS::ClassTemplate>
class ClassWithTemplateTemplateParam
{
public:
  static void staticMember()
  {
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }
};

template <int Count>
class NonTypeTemplateParam
{
public:
  void size() const
  {
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }
};

template <typename T>
class SpecializedClassTemplate
{
public:
  template <typename U>
  void memberFunctionTemplate(T t, U u) const
  {
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }
};

template <>
class SpecializedClassTemplate<int>
{
public:
  template <typename U>
  void memberFunctionTemplate(int i, U u) const
  {
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
  }
};

int main() {
  ClassInAnonymousNamespace anonymousNamespace;
  anonymousNamespace.anonymousNamespaceFunction();

  ClassInTopLevelNamespace topLevelNamespace;
  topLevelNamespace.topLevelNamespaceFunction();

  NS::Base::staticFunction();
  
  NS::Base b;
  b.inlineFunction();
  b.virtualFunction();
  b.variadicFunction(0);
  b.functionWithParameters(0, 0, 0);
  b.functionReturningClass();
  
  b.withTemplateParameter1(NS::ClassTemplate<int>());
  b.withTemplateParameter2(NS::ClassTemplate<NS::Base *>());
  b.functionReturingTemplate1();
  b.functionReturingTemplate2();
  b.functionTemplate1<int>(0);
  b.functionTemplate1<NS::Base *>(0);
  b.constFunction();
  b.volatileFunction();
  b.constVolatileFunction();
  b.refQualifiedFunction();
  NS::Base().refQualifiedFunction();

  NS::Derived d;
  d.virtualFunction();
  
  NS::ClassTemplate<int> t1;
  t1.classTemplateFunction();
  NS::ClassTemplate<NS::Base *> t2;
  t2.classTemplateFunction();
  
  NS::Constructor c1;
  NS::Constructor c2(0);
  NS::Constructor c3((NS::Base *)0);
  
  {
    NS::Destructor destructor;
  }

  NS::ContainerForAnonymousRecords anonymous; 
  anonymous.anonymousClass.anonymousClassFunction();
  anonymous.anonymousStruct.anonymousStructFunction();
  anonymous.anonymousUnion.anonymousUnionFunction();

  NS::localClass(0);

  NS::externFunction();


  functionTemplateWithTwoParams(0, 0.0f);
  functionTemplateWithoutParameterList<double>();
  functionTemplateWithTemplateReturnType<char>();
  int array[] = { 1, 2, 3 };
  functionTemplateWithCompoundTypes(array);
  functionTemplateExplicitSpecialization(0);
  functionTemplateExplicitSpecialization(0.0);
  functionTemplateWithUnnamedTemplateParameter<int, float>(0.0f);

  functionTemplateWithLambda<int>(0);
  functionTemplateWithCapturedStmt<int>(0);

  OuterClass<int *>::MiddleClass::InnerClass<float> omi;
  omi.memberFunction(0, 0.0f);

  ClassWithTemplateTemplateParam<char>::staticMember();

  NonTypeTemplateParam<42> ntt;
  ntt.size();

  SpecializedClassTemplate<int> sct1;
  sct1.memberFunctionTemplate(0, 0.0f);
  SpecializedClassTemplate<char> sct2;
  sct2.memberFunctionTemplate('0', 0.0);

  return 0;
}

class XXX {
  XXX();
  ~XXX();
};

void XXLog(const char *functionName) { }

// typedef void (^notify_handler_t)(int token);

// typedef void (^dispatch_block_t)(void);

// void notify_register_dispatch(notify_handler_t handler);

// void _dispatch_once(dispatch_block_t block);

XXX::XXX()
{
  //  _dispatch_once(^{ notify_register_dispatch( ^(int token) { XXLog(__FUNCTION__); }); 
  //  });
}

XXX::~XXX()
{
  //  _dispatch_once(^{ notify_register_dispatch( ^(int token) { XXLog(__FUNCTION__); }); 
  //  });
}
