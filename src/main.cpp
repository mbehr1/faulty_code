/*
 * (c) Matthias Behr, 2015
 * license: gpl v2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <list>
#include <string>

#include "gitSha1.h"

/*
 * todo list:
 *
 * + ex1: macros
 * + ex2: strncpy
 * + ex4: strdup/free
 * + ex3: constructor / virtual functions
 * + ex5: missing copy constructor/assignment op. and ref. counts
 * + ex6/7: std::list erase / iterator invalid
 * + ex6/7: std::list endless loop
 * + ex8: race conds
 * - pthread cancel async
 * - pthread cancel and semaphores
 * - shutdown / threads
 * - time complexity (O(n^2), qsort,...)
 * - watchdog / max. response time
 * - locks and thread prios / priority inversion
 * + ex12: wrong sequences (e.g. play before init/alloc,...)
 * + ex10: wrong cache
 * - "on change only" (if (a!=b) send_change )
 * - partial reads e.g. from backend,...
 * + ex13: missed start of com (serial,...)
 * - missing filesystems/interfaces at startup
 * - no more filehandles for that process (RLIMIT_NOFILE)
 * - too much memory / too big alloc.
 * - alsa return values (or generic handling return codes) (how to handle/simulate
 *	-EBADFD	PCM is not in the right state (SND_PCM_STATE_PREPARED or SND_PCM_STATE_RUNNING)
 *	-EPIPE	an underrun occurred
 *	-ESTRPIPE	a suspend event occurred (stream is suspended and waiting for an application recovery)
 * - blocking/non-blocking io
 * - wrong access rights (set)
 * - wrong tmp file location
 * - assertions/warnings (with fallback to default behaviour)
 * - time changes (& timeouts) (pthread_mutex_timedlock and stime)
 * - too many files included in binary delivery
 * - debug symbols included
 * - persistent data / versioning
 * - rt behaviour and memory lock (mlock/mlockall to avoid paging)
 * - floating point rounding/comparison
 * + ex11: signed/unsigned (if (iX - uY < 0 )...)
 * + ex9: delete[] (=new Foo[10]) -> not all destructors being called
 * - parameter parsing (scanf("%d", code);)
 * - porting code to 64bit (time_t) (see e.g. http://www.viva64.com/en/a/0004/)
 #define INVALID_RESULT (0xFFFFFFFFu)
 size_t MyStrLen(const char *str) {
	if (str == NULL)
	return INVALID_RESULT;
  ...
  return n;
  }
  size_t len = MyStrLen(str);
  if (len == (size_t)(-1))
 * ptrdiff_t SetBitN(ptrdiff_t value, unsigned bitNum) {
  ptrdiff_t mask = 1 << bitNum;
  return value | mask;
	}
	SetBitN(0, 31) SetBitN(0,32)
*/

// macros:
#include "macros.h"

void example1()
{
	// #define min(a,b) ((a)<(b) ? (a) : (b))
	// #define plus1_mult(a,b) ((a+1)*b)

	printf("plus1_mult(2,3)=%d\n", plus1_mult(2,3));
	printf("plus1_mult(2,2+1)=%d\n", plus1_mult(2,2+1));

	int a=1, b=1;
	printf("a=1, b=1. min(--a, b)=%d\n", min(--a, b));

}

void example2()
{
	char str1[4];
	char str2[]="0xdeadbeef";

	strncpy(str1, str2, sizeof(str1));
	printf("strlen(str1)=%d, str1=%s\n", strlen(str1), str1);
}

// example 3:
#include "classes.h"

void example3()
{
	ClassA a;
	printf(" = A:vfunc A?\n");
	ClassB b;
	printf(" = A:vfunc B B?\n");
}

void ex4(){
	char *test = new char[10];
	char *test2 = strndup(test, 10);
	if (strlen(test2)) {
		printf("strlen(test2)=%d\n", strlen(test2));
		free(test2);
	}
	delete [] test;
}

void ex5(){
	ClassC c("test");
	c.info();
	ClassC *d = new ClassC(c);
	d->info();
}

void ex6(int limit){
	std::list<int> ilist;
	ilist.push_front(1);
	ilist.push_back(2);
	ilist.push_back(3);

	auto it = ilist.begin();
	do{
		printf("*it = %d\n", *it);
		++it;
	}while (*it<=limit);

	it = ilist.begin();
	do{
		printf("*it = %d\n", *it);
		it = ilist.erase(it);
	}while (*it<=limit);
}

void ex7(int limit){
	std::list<int> ilist;
	ilist.push_back(1);
	ilist.push_back(2);
	ilist.push_back(3);
	for (auto it = ilist.begin(); *it<=limit && it!=ilist.end(); it=ilist.erase(it))
		printf("*it = %d\n", *it);
}

int ClassD::_nr_threads;

void ex8()
{
	assert(ClassD::_nr_threads==0);
	{
		ClassD d1;
		ClassD d2;
	}
	assert(ClassD::_nr_threads==0);

	ClassD *dx = new ClassD[2];
	usleep(10ul*1000);
	delete[] dx;
	if (ClassD::_nr_threads!=0) printf("ex8:ClassD::_nr_threads=%d\n", ClassD::_nr_threads);
	//while(ClassD::_nr_threads!=0) usleep(1000);
	// wrong signal/wakeup handling
}

void ex9()
{
	ClassD *dx = new ClassD[1];
	delete dx;
}

void ex10()
{
	ClassE cache;
	cache.add("test1");
	cache.add("test1");
	cache.add(std::string("test1"));
	printf("cache.size()=%d\n", cache.size());
	assert(cache.in_cache("test1"));
	std::string s1("test");
	s1.append("1");
	if (!cache.in_cache(s1.c_str()))
		printf("ex10: couldn't find test1\n" );
}

void ex11()
{
	int ix=10;
	unsigned int ux = 20;
	if (ix-ux < 0) {
		printf("ex11: <0\n");
	} else
		printf("ex11: >=0\n");
}

void ex12()
{
	ClassF interface;
	ClassG device(interface);
	bool ok;
	do {
		ok = device.run();
		if (!ok) printf("ex12: not ok!\n");
	} while (!ok);
}

void ex13(int scrap_pos)
{
	std::string header("deadbeef");
	std::string payload("1234567890123456789012");
	std::string cyclic = header;
	cyclic.append(payload);
	std::string scrap = payload.substr(scrap_pos);
	ClassH device(scrap, cyclic);
	bool header_found = false;
	do {
		std::string buf = device.read(10);
		printf("ex13: %s\n", buf.c_str());
		header_found = (buf.find(header) != std::string::npos);
	} while (!header_found);
}

int main(int argc, char *argv[])
{
	printf("%s version %s, last git commit %s\n", argv[0], g_GIT_SHALONG, g_GIT_LAST_COMMIT_DATE);

	example1();
	example2();
	example3();
	ex4();
	ex5();
	ex6(2);
//	ex6(3);
	ex7(3);
	ex8();
//	ex9();
	ex10();
	ex11();
	ex12();
	ex13(0);
//  ex13(3);
	return 0;
}
