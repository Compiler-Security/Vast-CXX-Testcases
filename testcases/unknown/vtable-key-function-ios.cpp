// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck




namespace std { class type_info; }
extern void use(const std::type_info &rtti);

/*** Test0a ******************************************************************/

struct Test0a {
  Test0a();
  virtual inline void foo();
  virtual void bar();
};

Test0a::Test0a() { use(typeid(Test0a)); }

void Test0a::foo() {}

/*** Test0b ******************************************************************/

struct Test0b {
  Test0b();
  virtual inline void foo();
  virtual void bar();
};

void Test0b::foo() {}

Test0b::Test0b() { use(typeid(Test0b)); }

/*** Test1a ******************************************************************/

struct Test1a {
  Test1a();
  virtual void foo();
  virtual void bar();
};

Test1a::Test1a() { use(typeid(Test1a)); }

inline void Test1a::foo() {}

/*** Test1b ******************************************************************/

struct Test1b {
  Test1b();
  virtual void foo();
  virtual void bar();
};

inline void Test1b::foo() {}

Test1b::Test1b() { use(typeid(Test1b)); }

/*** Test2a ******************************************************************/

struct Test2a {
  Test2a();
  virtual void foo();
  virtual void bar();
};

Test2a::Test2a() { use(typeid(Test2a)); }

void Test2a::bar() {}
inline void Test2a::foo() {}

/*** Test2b ******************************************************************/

struct Test2b {
  Test2b();
  virtual void foo();
  virtual void bar();
};

void Test2b::bar() {}

Test2b::Test2b() { use(typeid(Test2b)); }

inline void Test2b::foo() {}

/*** Test2c ******************************************************************/

struct Test2c {
  Test2c();
  virtual void foo();
  virtual void bar();
};

void Test2c::bar() {}
inline void Test2c::foo() {}

Test2c::Test2c() { use(typeid(Test2c)); }

/*** Test3a ******************************************************************/

struct Test3a {
  Test3a();
  virtual void foo();
  virtual void bar();
};

Test3a::Test3a() { use(typeid(Test3a)); }

inline void Test3a::bar() {}
inline void Test3a::foo() {}

/*** Test3b ******************************************************************/

struct Test3b {
  Test3b();
  virtual void foo();
  virtual void bar();
};

inline void Test3b::bar() {}

Test3b::Test3b() { use(typeid(Test3b)); }

inline void Test3b::foo() {}

/*** Test3c ******************************************************************/

struct Test3c {
  Test3c();
  virtual void foo();
  virtual void bar();
};

inline void Test3c::bar() {}
inline void Test3c::foo() {}

Test3c::Test3c() { use(typeid(Test3c)); }
