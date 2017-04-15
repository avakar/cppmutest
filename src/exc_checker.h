#ifndef AVAKAR_MUTEST_EXC_CHECKER_H
#define AVAKAR_MUTEST_EXC_CHECKER_H

#include "event_sink.h"

namespace mutest {
namespace detail {

template <typename E>
struct exc_checker
{
	template <typename F>
	static void check(F && f, char const * file, int line)
	{
		try
		{
			f();
			::mutest::global_exec_env().sink->check(false, file, line, "no exception thrown");
		}
		catch (E const &)
		{
		}
		catch (...)
		{
			::mutest::global_exec_env().sink->check(false, file, line, "unexpected exception thrown");
		}
	}
};

template <>
struct exc_checker<void>
{
	template <typename F>
	static void check(F && f, char const * file, int line)
	{
		try
		{
			f();
			::mutest::global_exec_env().sink->check(false, file, line, "no exception thrown");
		}
		catch (...)
		{
		}
	}
};

}
}

#endif // AVAKAR_MUTEST_EXC_CHECKER_H
