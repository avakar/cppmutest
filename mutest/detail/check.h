#ifndef CPPMUTEST_DETAIL_CHECK_H
#define CPPMUTEST_DETAIL_CHECK_H

#include "../event_sink.h"

namespace utest {
namespace detail {

struct check_proxy
{
	check_proxy(char const * file, int line)
		: m_file(file), m_line(line)
	{
	}

	template <typename T>
	void operator,(T && v)
	{
		if (!v)
			::utest::global_event_sink().fail(m_file, m_line);
	}

	char const * m_file;
	int m_line;
};

}
}

#endif // CPPMUTEST_DETAIL_CHECK_H
