#include "utest.h"

std::string utest::test::test_name() const
{
	return m_test_name;
}

class assertion_failed_error
	: public std::runtime_error
{
public:
	assertion_failed_error()
		: std::runtime_error("utest assertion failed")
	{
	}
};

struct default_event_sink
	: utest::event_sink
{
	void fail(char const * file, int line) override
	{
		throw assertion_failed_error();
	}

	void fail_eq(char const * file, int line) override
	{
		throw assertion_failed_error();
	}
};

int utest::main()
{
	default_event_sink ev;
	utest::event_sink_guard esg(ev);

	auto && tests = utest::global_registrar::get_tests();

	bool failed = false;
	for (auto && test: tests)
	{
		bool this_test_failed = false;
		try
		{
			test.fn()();
		}
		catch (assertion_failed_error const &)
		{
			this_test_failed = true;
		}

		if (this_test_failed)
			failed = true;
	}

	return failed? 1: 0;
}
