#ifndef MUTEST_COPY_ERROR_TESTER_H
#define MUTEST_COPY_ERROR_TESTER_H

#include <exception>

namespace mutest {

struct copy_error
	: std::exception
{
	char const * what() const noexcept override
	{
		return "mutest::copy_error";
	}
};

struct copy_error_tester
{
	struct value
	{
		explicit value(copy_error_tester & self)
			: m_self(self)
		{
		}

		value(value const & v)
			: m_self(v.m_self)
		{
			if (++m_self.m_cur_copies >= m_self.m_top_copies)
				throw copy_error();
		}

		value(value && v)
			: m_self(v.m_self)
		{
		}

	private:
		copy_error_tester & m_self;
	};

	copy_error_tester()
		: m_cur_copies(0), m_top_copies(0)
	{
	}

	bool next()
	{
		bool thrown = !this->good();
		++m_top_copies;
		m_cur_copies = 0;
		return thrown;
	}

	bool good() const
	{
		return m_cur_copies < m_top_copies;
	}

	value get()
	{
		return value(*this);
	}

private:
	size_t m_cur_copies;
	size_t m_top_copies;
};

}

#endif // MUTEST_COPY_ERROR_TESTER_H
