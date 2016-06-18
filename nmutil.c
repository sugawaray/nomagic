#include <nomagicc.h>
#include <stdio.h>
#include <stdarg.h>

static int ind;
static char buf[10][128];

const char *
testmsg(const char *fmt, ...)
{
	int sz;
	char *r;
	va_list ap;

	sz = sizeof buf[0] / sizeof buf[0][0];

	va_start(ap, fmt);
	vsnprintf(buf[ind], sz, fmt, ap);
	va_end(ap);

	buf[ind][sz - 1] = '\0';

	r = buf[ind];

	++ind;
	if (ind >= (int)(sizeof buf / sizeof buf[0]))
		ind = 0;
	return r;
}
