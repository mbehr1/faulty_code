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

class ClassC
{
public:
	ClassC (const char *str) : _str(strdup(str)) {};
	~ClassC() { free (_str); };
	void info() { printf ("str %p = %s\n", _str, _str); };

protected:
	char *_str;
};

#endif
