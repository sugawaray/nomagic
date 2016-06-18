#ifndef NOMAGICC_H
#define NOMAGICC_H	1

void testerror(const char *message);
void testrun(const char *message, void (*f)());
const char *testmsg(const char *format, ...);

#endif
