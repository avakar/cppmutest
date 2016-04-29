#include <utest.h>

UTEST_TEST("Hello world")
{
	// This test is a part of a suite `Suite` and is named `HelloWorld`.
	// Case matters. The test will be referred to by the framework
	// as `Suite:HelloWorld`. Pass this name on the command line
	// to run this test only.
}

UTEST_TEST("it shall support simple comparisons")
{
	UTEST_ASSERT_EQ(1, 1);
}

int main()
{
	return utest::main();
}
