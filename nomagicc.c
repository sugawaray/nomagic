#include <nomagicc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static
int
getresult(int status)
{
	if (WIFSIGNALED(status))
		return 1 << 8;
	else if (WIFEXITED(status))
		return WEXITSTATUS(status);
	else
		return 1 << 16;
}

static int nerr;
static char buf[2048];
static int bpos;

static
void
reset()
{
	nerr = 0;
	bpos = 0;
	memset(&buf, 0, sizeof buf);
}

void
testerror(const char *m)
{
	size_t l1, l2;
	const char *err = "TESTERROR: message buffer is not enough.";
	const char *detail = "DETAIL: ";

	l1 = strlen(detail);
	l2 = strlen(m);
	if (sizeof buf - bpos <= l1 + l2 + 1) {
		fprintf(stderr, "%s\n", err);
		exit(1);
	}
	sprintf(buf + bpos, "%s%s\n", detail, m);
	++nerr;
}

void
testrun(const char *m, void (*f)())
{
	pid_t id;

	reset();
	errno = 0;
	id = fork();
	if (id == 0) {
		f(m);
		if (nerr > 0)
			fprintf(stderr, "FAIL: %s\n%s", m, buf);
		else
			fprintf(stderr, "PASS: %s\n", m);
		exit(0);
	} else if (id != -1) {
		int status;
		int r;
		if (waitpid(id, &status, 0) != id)
			perror("TESTERROR: waitpid");
		else if ((r = getresult(status)) != 0)
			fprintf(stderr, "FAIL: %s(%d)\n", m, r);
	} else {
		perror("TESTERROR: fork");
		exit(1);
	}
}
