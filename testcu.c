#include "nomagicc.h"
#include "nomagiccu.h"
#include <string.h>

#define S(x)	#x
#define A(e)	do { if (!(e)) { testerror(S(x)); } } while (0)

static
void
hex1()
{
	const char *p;

	p = testmeqh(-1, 0);
	A(strcmp(p, "0x00000000 != 0xFFFFFFFF") == 0);
}

static
void
multi()
{
	const char *p, *q;

	p = testmeqh(-1, 0);
	q = testmeqh(-2, 1);
	A(strcmp(p, "0x00000000 != 0xFFFFFFFF") == 0);
	A(strcmp(q, "0x00000001 != 0xFFFFFFFE") == 0);
}

int
main()
{
	testrun("hex 1", hex1);
	testrun("can call several times", multi);
	return 0;
}
