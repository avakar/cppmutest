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
	chk (unsigned char)200 == 0;

	chk true && false;
	chk 1 == 1;
	chk 1 != 1;
}

TEST("it shall support failing tests #fails")
{
	chk 1 == 2;
}
