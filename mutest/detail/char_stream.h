#ifndef CPPMUTEST_MUTEST_DETAIL_CHAR_STREAM_H
#define CPPMUTEST_MUTEST_DETAIL_CHAR_STREAM_H

namespace mutest {
namespace detail {

struct char_stream
{
	char_stream(char * buf, size_t len)
		: m_first(buf), m_cur(buf), m_last(buf + len - 1)
	{
	}

	void append(char v)
	{
		if (m_cur != m_last)
			*m_cur++ = v;
	}

	void append(char const * v)
	{
		while (m_cur != m_last && *v)
			*m_cur++ = *v++;
	}

	void finalize()
	{
		*m_cur = 0;
	}

private:
	char * m_first;
	char * m_cur;
	char * m_last;
};

}
}

#endif // CPPMUTEST_MUTEST_DETAIL_CHAR_STREAM_H
