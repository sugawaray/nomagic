#include <nomagicc.h>
#include <stdio.h>
#include <stdlib.h>

void
t1()
{
}

void
t2()
{
	exit(1);
}

void
t3()
{
	testerror("error1");
}

void
t4()
{
	testerror("error1");
	testerror("error2");
}

int
main()
{
	printf("#Test start: success cases' outputs\n");
	printf("#should output 'PASS: message A'\n");
	testrun("message A", t1);
	printf("#Test end: success cases' outputs\n");

	printf("#Test start: failure cases' outputs\n");
	printf("#should output 'FAIL: message A'\n");
	testrun("message A", t2);
	printf("#Test end: failure cases' outputs\n");

	printf("#Test start: failure cases' outputs(assertion)\n");
	printf("#should output like below\n");
	printf("#'FAIL: message A'\n");
	printf("#'DETAIL: error1'\n");
	testrun("message A", t3);
	printf("#Test end: failure cases' outputs(assertion)\n");

	printf("#Test start: multiple testerror calls\n");
	printf("#should output like below\n");
	printf("#'FAIL: message A'\n");
	printf("#'DETAIL: error1'\n");
	printf("#'DETAIL: error2'\n");
	testrun("message A", t4);
	printf("#Test end: multiple testerror calls\n");
}
