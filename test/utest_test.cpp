#include <mutest/test.h>

TEST("hello world")
{
	// This test is named "hello world". Test names should be chosen
	// so that they describe the functionality under test.
	// The name will appear on output if the test fails.
	//
	// The names need not be unique, but you should strive for them to be.
	//
	// You can run only specific tests by passing a regular expression
	// matching the test name on the command line.
}

TEST("it shall support simple checks")
{
	chk true;
	chk !false;
}

TEST("it shall support simple comparisons")
{
	chk 1 == 1;
	chk 1 != 2;
	chk 1 < 2;
	chk 2 > 1;
	chk 1 <= 1;
	chk 1 >= 1;
}

TEST("it shall support complex comparisons")
{
	chk 1 + 1 == 2;
	chk 1 << 1 == 2;
}
