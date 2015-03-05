#include "utest.h"

std::string utest::test::suite_name() const
{
	return m_suite_name;
}

std::string utest::test::case_name() const
{
	return m_case_name;
}

std::vector<std::string> utest::parse_tags(char const * tags)
{
	std::vector<std::string> res;

	if (tags)
	{
		char const * tag_start = tags;
		for (; *tags; ++tags)
		{
			if (*tags != ' ')
				continue;

			if (tag_start != tags)
				res.push_back(std::string(tag_start, tags));

			tag_start = tags + 1;
		}

		if (tag_start != tags)
			res.push_back(std::string(tag_start, tags));
	}

	return res;
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

		for (auto && tag: test.tags())
		{
			if (tag == "!fails")
				this_test_failed = !this_test_failed;
		}

		if (this_test_failed)
			failed = true;
	}

	return failed? 1: 0;
}
