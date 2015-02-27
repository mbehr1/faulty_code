#include <stdio.h>

#include "gitSha1.h"

int main(int argc, char *argv[])
{
	printf("%s version %s, last git commit %s\n", argv[0], g_GIT_SHALONG, g_GIT_LAST_COMMIT_DATE);

	return 0;
}
