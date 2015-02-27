/*
 * (c) Matthias Behr, 2015
 * license: gpl v2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>

#include "gitSha1.h"

/*
 * todo list:
 *
 * + ex1: macros
 * + ex2: strncpy
 * + ex4: strdup/free
 * + ex3: constructor / virtual functions
 * + ex5: missing copy constructor/assignment op. and ref. counts
 * - recursion
 * + ex6/7: std::list erase / iterator invalid
 * - std::list endless loop
 * - race conds
 * - pthread cancel async
 * - pthread cancel and semaphores
 * - shutdown / threads
 * - time complexity (O(n^2), qsort,...)
 * - watchdog / max. response time
 * - wrong sequences
 * - locks and thread prios / priority inversion
 * - wrong cache
 * - "on change only" (if (a!=b))
 * - partial reads
 * - missed start of com (serial,...)
 * - missing filesystems/interfaces at startup
 * - no more filehandles
 * - too much memory / too big alloc.
 * - alsa return values (or generic handling return codes)
 * - blocking/non-blocking io
 * - wrong access rights (set)
 * - wrong tmp file location
 * - assertions/warnings (default behaviour)
 * - time changes (& timeouts)
 * - too many files included
 * - debug symbols included
 * - persistent data / versioning
 * - rt behaviour and memory lock (avoid paging)
 *
 *
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

	return 0;
}
