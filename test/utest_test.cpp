#include <mutest/test.h>
#include <string>

TEST("Hello world")
{
	// This test is a part of a suite `Suite` and is named `HelloWorld`.
	// Case matters. The test will be referred to by the framework
	// as `Suite:HelloWorld`. Pass this name on the command line
	// to run this test only.
}

TEST("it shall support simple comparisons")
{
	void * ptr = 0;
	//chk ptr;

	std::string str = "test";
	chk str != "test";

	chk 1 == 1;
	chk true;
	chk 1 != 1;
}

TEST("it shall support failing tests #fails")
{
	chk 1 == 2;
}
