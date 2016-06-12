#include <nomagiccu.h>
#include <stdio.h>

static int ind;
static char buf[10][128];

const char *
testmeqh(int x, int a)
{
	int sz;
	char *r;

	sz = sizeof buf[0] / sizeof buf[0][0];
	snprintf(buf[ind], sz, "0x%08X != 0x%08X", a, x);
	buf[ind][sz - 1] = '\0';

	r = buf[ind];

	++ind;
	if (ind >= (int)(sizeof buf / sizeof buf[0]))
		ind = 0;
	return r;
}
