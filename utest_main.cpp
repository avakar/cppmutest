#include "mutest/utest.h"
#include "exec.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <assert.h>

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
	: mutest::event_sink
{
	default_event_sink()
	{
	}

	void check(bool success, char const * file, int line, char const * msg) override
	{
		if (success)
		{
			std::cout << file << "(" << line << "): note: " << msg << "\n";
		}
		else
		{
			std::cout << file << "(" << line << "): error: " << msg << "\n";
			throw assertion_failed_error();
		}
	}
};

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

int mutest::master_main(int argc, char const * const argv[])
{
	std::vector<std::regex> patterns;
	auto & env = global_exec_env();
	default_event_sink ev;

	parse_args(argc, argv, [&](char const * opt, arg_shifter & args) {
		if (strcmp(opt, "-v") == 0)
		{
			env.verbose = true;
		}
		else
		{
			throw std::runtime_error(std::string("unknown option: ") + opt);
		}
	}, [&](char const * arg) {
		patterns.push_back(std::regex(arg, std::regex_constants::icase));
	});

	auto should_run = [&](mutest::test_list_entry const & test) -> bool {
		if (patterns.empty())
			return true;

		for (std::regex const & re: patterns)
		{
			if (std::regex_search(test.name, re))
				return true;
		}

		return false;
	};

	env.sink = &ev;

	auto && tests = mutest::global_registrar::head();

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
		catch (std::exception const & e)
		{
			std::cout << test.file << "(" << test.line << "): error: " << typeid(e).name() << ": " << e.what() << "\n";
			this_test_failed = true;
		}
		catch (...)
		{
			std::cout << test.file << "(" << test.line << "): error: unrecognized exception was thrown\n";
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
	return mutest::master_main(argc - 1, argv + 1);
}
