#include <utest.h>

UTEST_TEST(Suite, HelloWorld)
{
	// This test is a part of a suite `Suite` and is named `HelloWorld`.
	// Case matters. The test will be referred to by the framework
	// as `Suite:HelloWorld`. Pass this name on the command line
	// to run this test only.
	//
	// Categorizing tests into suites serves little function, but is done
	// for compatibility with googletest.
}

UTEST_TEST(DifferentSuite, Test)
{
	// Usually, you'll give all the tests for a single component the same suite name,
	// but nothing prevents you from doing otherwise. This test is named
	// `DifferentSuite:Test`.
}

UTEST_TEST(Suite, WithTags, "tag")
{
	// Give your test a space-separated list of tags;
	// passing one of the tags on the command line will select
	// the test.
}

namespace my_namespace {

UTEST_TEST(Suite, HelloWorld)
{
	// This test shall not conflict with the other `Suite:HelloWorld` test
	// even though they are named the same. Each namespace establishes
	// a new scope for the tests.
	//
	// Note however, that the names are the same and no filter will be able
	// to differentiate between them.
}

}

UTEST_TEST(Suite, TestCaseNaming)
{
	// The tests are callables with a specific name.
	utest::test_fn fn = ::Suite_HelloWorld_utest;
	fn = ::my_namespace::Suite_HelloWorld_utest;
	(void)fn;
}

// The real naming of the tests shall not conflict with stuff
void SuiteHelloWorld() {}
void Suite_HelloWorld() {}

UTEST_TEST(Suite, ShallSucceed)
{
	UTEST_ASSERT_EQ(1, 1);
}

UTEST_TEST(Suite, ShallFail, "!fails")
{
	UTEST_ASSERT_EQ(1, 2);
}

#include <vector>

UTEST_TEST(Suite, AutoRegistry)
{
	auto && tests = ::utest::global_registrar::get_tests();
	std::vector<::utest::test> test_vec(begin(tests), end(tests));
}

UTEST_TEST(Suite, TestsHaveNames)
{
	bool found_self = false;
	for (auto && test: ::utest::global_registrar::get_tests())
	{
		if (test.suite_name() == "Suite" && test.case_name() == "TestsHaveNames")
			found_self = true;
	}

	UTEST_ASSERT_TRUE(found_self);
}

UTEST_TEST(Suite, TestsHaveNamesAndTags, "tag")
{
	bool found_self = false;
	for (auto && test : ::utest::global_registrar::get_tests())
	{
		if (test.suite_name() == "Suite" && test.case_name() == "TestsHaveNamesAndTags")
		{
			auto && tags = test.tags();
			UTEST_ASSERT_EQ(tags.size(), 1);
			UTEST_ASSERT_EQ(tags[0], "tag");
			found_self = true;
			break;
		}
	}

	UTEST_ASSERT_TRUE(found_self);
}

int main()
{
	return utest::main();
}
