// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {};

struct B 
{ 
  operator A&();
}; 


struct D : public B {
  operator A();
};

extern B f(); 
extern D d(); 

int main() {
	const A& rca = f();
	const A& rca2 = d();
}

