#include "mutest/utest.h"
#include "exec.h"
#include <iostream>

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

#include <assert.h>

struct arg_shifter
{
	arg_shifter(int argc, char const * const argv[])
		: m_argc(argc), m_argv(argv)
	{
	}

	char const * shift()
	{
		assert(!this->done());
		char const * res = *m_argv;
		++m_argv;
		--m_argc;
		return res;
	}

	bool done() const
	{
		return m_argc == 0;
	}

	int m_argc;
	char const * const * m_argv;
};

template <typename Opts, typename Args>
void parse_args(int argc, char const * const argv[], Opts process_opt, Args process_arg)
{
	arg_shifter args(argc, argv);

	while (!args.done())
	{
		char const * arg = args.shift();

		if (arg[0] != '-')
		{
			process_arg(arg);
			continue;
		}

		if (arg[1] == '-')
		{
			if (arg[2] == 0)
				break;
			process_opt(arg, args);
			continue;
		}

		char const * opt = arg + 1;
		while (*opt != 0)
		{
			char full_opt[3] = { '-', *opt++, 0 };
			process_opt(full_opt, args);
		}
	}

	while (!args.done())
		process_arg(args.shift());
}

#include <string>
#include <vector>
#include <regex>

int utest::master_main(int argc, char const * const argv[])
{
	std::vector<std::regex> patterns;
	parse_args(argc, argv, [&](char const * opt, arg_shifter & args) {
		throw std::runtime_error(std::string("unknown option: ") + opt);
	}, [&](char const * arg) {
		patterns.push_back(std::regex(arg, std::regex_constants::icase));
	});

	auto should_run = [&](utest::test_list_entry const & test) -> bool {
		if (patterns.empty())
			return true;

		for (std::regex const & re: patterns)
		{
			if (std::regex_search(test.name, re))
				return true;
		}

		return false;
	};

	default_event_sink ev;
	utest::event_sink_guard esg(ev);

	auto && tests = utest::global_registrar::head();

	bool failed = false;
	for (auto && test: tests)
	{
		if (!should_run(test))
			continue;

		std::cout << test.name << "\n";

		bool this_test_failed = false;
		try
		{
			test.fn();
		}
		catch (assertion_failed_error const &)
		{
			this_test_failed = true;
		}

		if (strstr(test.name, "#fails"))
			this_test_failed = !this_test_failed;

		if (this_test_failed)
			failed = true;
	}

	return failed? 1: 0;
}

int main(int argc, char * argv[])
{
	return utest::master_main(argc - 1, argv + 1);
}
