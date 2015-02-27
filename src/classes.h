#ifndef __classes_h__
#define __classes_h__

class ClassA
{
public:
	ClassA() { printf(" A"); vfunc1();};
	virtual void vfunc1(){ printf(":vfunc A");};
};

class ClassB : public ClassA
{
public:
	ClassB() : ClassA() { printf(" B"); }
	virtual void vfunc1(){ printf(":vfunc B");};
};

#endif
