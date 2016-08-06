#include <nomagicc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static int ind;
static char buf[10][128];
static int lind;
static char *lbuf[10];

const char *
testmsg(const char *fmt, ...)
{
	int sz, ir;
	char *r;
	va_list ap;

	sz = sizeof buf[0] / sizeof buf[0][0];

	va_start(ap, fmt);
	ir = vsnprintf(buf[ind], sz, fmt, ap);
	va_end(ap);

	if (ir >= sz) {
		lbuf[lind] = realloc(lbuf[lind], ir + 1);
		va_start(ap, fmt);
		vsnprintf(lbuf[lind], ir + 1, fmt, ap);
		va_end(ap);

		r = lbuf[lind];
		++lind;
		if (lind >= (int)(sizeof lbuf / sizeof lbuf[0]))
			lind = 0;
	} else {
		r = buf[ind];
	
		++ind;
		if (ind >= (int)(sizeof buf / sizeof buf[0]))
			ind = 0;
	}
	return r;
}

const char *
testmem(const char *mem, int sz)
{
	int i, r, y, msz, pos;
	char *p, *q;
	const unsigned char *m = (const unsigned char *)mem;

	y = sz / 16 + ((sz % 16) ? 1 : 0);
	msz = sz * 3 + y * 9 + 1;
	lbuf[lind] = realloc(lbuf[lind], msz);
	p = lbuf[lind];
	q = p + msz;
	for (i = 0; i < sz; ++i) {
		pos = i % 16;
		if (pos == 0)
			r = snprintf(p, q - p, "%07x %02x ", i, m[i]);
		else if (pos == 15)
			r = snprintf(p, q - p, "%02x\n", m[i]);
		else
			r = snprintf(p, q - p, "%02x ", m[i]);
		if (r < 0 || r >= q - p)
			return "testmem error";
		else
			p += r;
	}
	p = lbuf[lind];
	++lind;
	if (lind >= (int)(sizeof lbuf / sizeof lbuf[0]))
		lind = 0;
	return p;
}
