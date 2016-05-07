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
		char buf[256];
		char_stream ss(buf, sizeof buf);
		if (!v.e.check(ss))
		{
			ss.finalize();
			::mutest::global_event_sink().fail(m_file, m_line, buf);
		}
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
