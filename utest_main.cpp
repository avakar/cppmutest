#include "utest.h"

std::string utest::test::test_name() const
{
	return m_test_name;
}

int utest::main()
{
	auto && tests = utest::global_registrar::get_tests();

	bool failed = false;
	for (auto && test: tests)
	{
		bool this_test_failed = false;
		try
		{
			test.fn()();
		}
		catch (utest::assertion_failed_error const &)
		{
			this_test_failed = true;
		}

		if (this_test_failed)
			failed = true;
	}

	return failed? 1: 0;
}
