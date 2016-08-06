#include "nomagicc.h"
#include <stdio.h>
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

static
void
msglarge()
{
	int i, j;
	const char *p, *q, *r, *s;
	unsigned char b[2][0x100];

	for (i = 0; i < sizeof b / sizeof b[0]; ++i)
		for (j = 0; j < sizeof b[i] / sizeof b[i][0]; ++j)
			b[i][j] = i + j;
	p = testmsg("short message 1");
	q = testmsg(testmem((char*)b[0], sizeof b[0]));
	r = testmsg(testmem((char*)b[1], sizeof b[1]));
	s = testmsg("short message 2");
	fprintf(stderr, "[%s][\n%s]\n[\n%s]\n[%s]\n", p, q, r, s);
}

static
void
mempr()
{
	unsigned char b[0x100];
	int i;

	for (i = 0; i < sizeof b / sizeof b[0]; ++i)
		b[i] = i;
	fprintf(stderr, "[\n%s]\n", testmem((char*)b, sizeof b));
}

static
void
memprmulti()
{
	int i, j;
	const char *p, *q;
	unsigned char b[2][0x100];

	for (i = 0; i < sizeof b / sizeof b[0]; ++i)
		for (j = 0; j < sizeof b[i] / sizeof b[i][0]; ++j)
			b[i][j] = i + j;
	p = testmem((char*)b[0], sizeof b[0]);
	q = testmem((char*)b[1], sizeof b[1]);
	fprintf(stderr, "[\n%s]\n[\n%s]\n", p, q);
}

static
void
combi()
{
	int i, j;
	unsigned char b[2][0x100];

	for (i = 0; i < sizeof b / sizeof b[0]; ++i)
		for (j = 0; j < sizeof b[i] / sizeof b[i][0]; ++j)
			b[i][j] = i + j;
	testerror(testmsg("memdiff\nexpect\n%sactual\n%s", testmem((char*)b[0],  sizeof b[0]), testmem((char*)b[1], sizeof b[1])));
}

int
main()
{
	testrun("testmsg: can call several times", multi);
	testrun("testmsg: manual test : can deal with large msgs", msglarge);
	testrun("testmem: manual test : can call several times", memprmulti);
	testrun("testmem: manual test", mempr);
	testrun("manual test: combination", combi);
	return 0;
}
