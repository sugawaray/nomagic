#include "nomagicc.h"
#include <string.h>

#define S(x)	#x
#define A(e)	do { if (!(e)) { testerror(S(x)); } } while (0)

void
multi()
{
	const char *p, *q;

	p = testmsg("message 1st");
	q = testmsg("message 2nd");
	A(strcmp(p, "message 1st") == 0);
	A(strcmp(q, "message 2nd") == 0);
}

int
main()
{
	testrun("testmsg: can call several times", multi);
	return 0;
}
