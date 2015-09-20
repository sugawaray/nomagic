#include <cassert>
#include <iostream>
#include <string>
#include "nomagic.h"

using std::cout;
using std::endl;
using std::string;
using nomagic::run;
using nomagic::Test;

namespace {

void success()
{
	cout << "success()" << endl;
	cout << "Good message" << endl;
}

void failure()
{
	throw 1;
}

void failure_assert()
{
	assert(0);
}

void called_with_message(const char* message)
{
	cout << "called_with_message:" << message << endl;
}

template<class F>
void dorun(const string& m, F f)
{
	cout << endl;
	cout << m << " start" << endl;
	run("Good message if failures are expected.", f);
	cout << m << " end" << endl;
}

namespace ntest {

typedef ::nomagic::Test T;

void t1()
{
	T t("Not good message");
	t.a(true, "Not good a");
	t.a(true, string("Not good b"));
	t.a(true, 0);
}

void t2()
{
	T t("Good message");
	t.a(false, "ok output 1");
	t.a(true, "not ok output 2");
	t.a(false, string("ok output 2"));
	t.a(false, 0);
	cout << "3 messages should be output." << endl;
}

} // ntest

namespace nloc {

void t1(const char* m)
{
	Test t(m);
	t.a(nomagic::loc("a", 1) == "a(1)", "1");
}

} // nloc

} // unnamed

int main()
{
	cout << "test start" << endl;
	dorun("t1", success);
	dorun("t2(expect failures)", failure);
	dorun("t3(expect failures)", failure_assert);
	dorun("t4", called_with_message);

	dorun(	"Test does not output any messages when there are not "
		"any failure.", ntest::t1);

	dorun("Test outputs messages when there are failures.", ntest::t2);
	cout << endl;

	run("create a file and line string", nloc::t1);

	cout << "test end" << endl;
	return 0;
}
