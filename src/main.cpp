/*
 * (c) Matthias Behr, 2015
 * license: gpl v2
 */

#include <stdio.h>
#include <string.h>

#include "gitSha1.h"

/*
 * todo list:
 *
 * + macros
 * + strncpy
 * + constructor / virtual functions
 * - race conds
 * - pthread cancel
 * - time complexity
 * - recursion
 * - std::list erase / iterator invalid
 * - watchdog
 * - wrong sequences
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

int main(int argc, char *argv[])
{
	printf("%s version %s, last git commit %s\n", argv[0], g_GIT_SHALONG, g_GIT_LAST_COMMIT_DATE);

	// 1. macros:
	example1();

	// 2. strncpy
	example2();

	// 3. constructor virt
	example3();

	return 0;
}
