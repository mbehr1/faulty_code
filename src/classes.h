#ifndef __classes_h__
#define __classes_h__

#include <pthread.h>
#include <list>
#include <string>

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

class ClassD
{
public:
	ClassD() : _stop(false) { pthread_create(&_tid, 0, fn, this); };
	~ClassD() { _stop = true; assert(0==pthread_join(_tid, 0)); };
	static void* fn(void *arg) { ClassD *d = (ClassD*)arg; while (!d->_stop) { ++_nr_threads; --_nr_threads; }; return 0;};

	pthread_t _tid;
	bool _stop;
	static int _nr_threads;
};

class ClassE
{
public:
	ClassE(){};
	void add(const std::string &r) { add(r.c_str()); };
	void add(const char *item) { if (!in_cache(item)) _cache.push_front(item);};
	bool in_cache(const char *item) {
		for (auto it=_cache.cbegin(); it!= _cache.cend(); ++it) {
			if (item == *it) return true;
		}
		return false;
	};
	size_t size() const { return _cache.size(); };

protected:
	std::list<const char *> _cache;
};

class ClassF
{
public:
	ClassF() : _init(false) {};
	void init() { _init = true; }
	bool play() {if (!_init) return false; return true; }

protected:
	bool _init;
};

class ClassG
{
public:
	ClassG(ClassF &interface) : _interface(interface) {};
	bool run() { bool b = _interface.play(); if (!b) _interface.init();  return b;}
protected:
	ClassF &_interface;
};

class ClassH
{
public:
	ClassH(const std::string &start, const std::string &cyclic) : _pos(0), _start(start), _cyclic(cyclic) {};
	std::string read(unsigned int size) {
		unsigned int opos = _pos;
		std::string ret;
		if (!size) return ret;
		if (_pos<_start.length())
			ret = _start.substr(_pos, size);
		_pos += ret.length();
		unsigned int remain = size - ret.length();
		if (remain && _cyclic.length()>0) {
			do {
				ret.append(_cyclic, (_pos - _start.length()) % _cyclic.length(), remain);
				remain = size - ret.length();
				_pos = opos + size - remain;
			} while(remain > 0);
		}
		return ret;}

protected:
	unsigned int _pos;
	std::string _start;
	std::string _cyclic;
};

#endif
