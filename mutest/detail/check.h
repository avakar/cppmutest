#ifndef CPPMUTEST_DETAIL_CHECK_H
#define CPPMUTEST_DETAIL_CHECK_H

#include "../event_sink.h"
#include "char_stream.h"
#include "repr.h"
#include "binary_op.h"
#include "expr.h"

namespace mutest {
namespace detail {

struct check_proxy
{
	check_proxy(char const * file, int line)
		: m_file(file), m_line(line)
	{
	}

	template <typename T>
	void operator,(expr<T> const & v)
	{
		auto const & env = ::mutest::global_exec_env();

		char buf[256];
		char_stream ss(buf, sizeof buf);
		bool success = v.e.check(ss, env.verbose);
		ss.finalize();

		if (!success || env.verbose)
			::mutest::global_exec_env().sink->check(success, m_file, m_line, buf);
	}

private:
	char const * m_file;
	int m_line;
};

struct init_expr
{
	template <typename T>
	expr<value_expr<T>> operator<<(T const & v)
	{
		return value_expr<T>(v);
	}
};

} // namespace detail
} // namespace mutest

#endif // CPPMUTEST_DETAIL_CHECK_H
