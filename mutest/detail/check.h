#ifndef CPPMUTEST_DETAIL_CHECK_H
#define CPPMUTEST_DETAIL_CHECK_H

#include "../event_sink.h"
#include "char_stream.h"
#include "repr.h"
#include "binary_op.h"

namespace mutest {
namespace detail {

struct check_proxy
{
	check_proxy(char const * file, int line)
		: m_file(file), m_line(line)
	{
	}

	template <typename T>
	void operator,(T const & v)
	{
		char buf[256];
		char_stream ss(buf, sizeof buf);
		if (!v.check(ss))
		{
			ss.finalize();
			::utest::global_event_sink().fail(m_file, m_line, buf);
		}
	}

private:
	char const * m_file;
	int m_line;
};

template <typename T>
struct value_expr
{
	explicit value_expr(T const & value)
		: m_value(value)
	{
	}

	bool check(char_stream & ss) const
	{
		if (!m_value)
		{
			repr(ss, m_value);
			return false;
		}
		return true;
	}

	T const & value() const
	{
		return m_value;
	}

private:
	T const & m_value;
};

struct init_expr
{
	template <typename T>
	value_expr<T> operator<<(T const & v)
	{
		return value_expr<T>(v);
	}
};

template <typename L, typename R, binary_op Op>
struct binary_op_expr
{
	binary_op_expr(L const & lhs, R const & rhs)
		: m_lhs(lhs), m_rhs(rhs)
	{
	}

	L const & m_lhs;
	R const & m_rhs;

	bool check(char_stream & ss) const
	{
		auto && lhs = m_lhs.value();
		bool res = binary_op_eval<Op>::eval(lhs, m_rhs);
		if (!res)
		{
			repr(ss, lhs);
			ss.append(' ');
			ss.append(binary_op_eval<Op>::text());
			ss.append(' ');
			repr(ss, m_rhs);
		}
		return res;
	}

	auto value() const -> decltype(this->m_lhs.value() == this->m_rhs)
	{
		return binary_op_eval<Op>::eval(m_lhs.value(), m_rhs);
	}
};

template <typename T, typename R>
binary_op_expr<value_expr<T>, R, binary_op::eq> operator==(value_expr<T> const & lhs, R const & rhs)
{
	return binary_op_expr<value_expr<T>, R, binary_op::eq>(lhs, rhs);
}

template <typename T, typename R>
binary_op_expr<value_expr<T>, R, binary_op::neq> operator!=(value_expr<T> const & lhs, R const & rhs)
{
	return binary_op_expr<value_expr<T>, R, binary_op::neq>(lhs, rhs);
}

template <typename T, typename R>
binary_op_expr<value_expr<T>, R, binary_op::lt> operator<(value_expr<T> const & lhs, R const & rhs)
{
	return binary_op_expr<value_expr<T>, R, binary_op::lt>(lhs, rhs);
}

template <typename T, typename R>
binary_op_expr<value_expr<T>, R, binary_op::leq> operator<=(value_expr<T> const & lhs, R const & rhs)
{
	return binary_op_expr<value_expr<T>, R, binary_op::leq>(lhs, rhs);
}

template <typename T, typename R>
binary_op_expr<value_expr<T>, R, binary_op::gt> operator>(value_expr<T> const & lhs, R const & rhs)
{
	return binary_op_expr<value_expr<T>, R, binary_op::gt>(lhs, rhs);
}

template <typename T, typename R>
binary_op_expr<value_expr<T>, R, binary_op::geq> operator>=(value_expr<T> const & lhs, R const & rhs)
{
	return binary_op_expr<value_expr<T>, R, binary_op::geq>(lhs, rhs);
}

template <typename LL, typename LR, binary_op LOp, typename R>
binary_op_expr<binary_op_expr<LL, LR, LOp>, R, binary_op::eq> operator==(binary_op_expr<LL, LR, LOp> const & lhs, R const & rhs)
{
	return binary_op_expr<binary_op_expr<LL, LR, LOp>, R, binary_op::eq>(lhs, rhs);
}

template <typename LL, typename LR, binary_op LOp, typename R>
binary_op_expr<binary_op_expr<LL, LR, LOp>, R, binary_op::neq> operator!=(binary_op_expr<LL, LR, LOp> const & lhs, R const & rhs)
{
	return binary_op_expr<binary_op_expr<LL, LR, LOp>, R, binary_op::neq>(lhs, rhs);
}

template <typename LL, typename LR, binary_op LOp, typename R>
binary_op_expr<binary_op_expr<LL, LR, LOp>, R, binary_op::lt> operator<(binary_op_expr<LL, LR, LOp> const & lhs, R const & rhs)
{
	return binary_op_expr<binary_op_expr<LL, LR, LOp>, R, binary_op::lt>(lhs, rhs);
}

template <typename LL, typename LR, binary_op LOp, typename R>
binary_op_expr<binary_op_expr<LL, LR, LOp>, R, binary_op::leq> operator<=(binary_op_expr<LL, LR, LOp> const & lhs, R const & rhs)
{
	return binary_op_expr<binary_op_expr<LL, LR, LOp>, R, binary_op::leq>(lhs, rhs);
}

template <typename LL, typename LR, binary_op LOp, typename R>
binary_op_expr<binary_op_expr<LL, LR, LOp>, R, binary_op::gt> operator>(binary_op_expr<LL, LR, LOp> const & lhs, R const & rhs)
{
	return binary_op_expr<binary_op_expr<LL, LR, LOp>, R, binary_op::gt>(lhs, rhs);
}

template <typename LL, typename LR, binary_op LOp, typename R>
binary_op_expr<binary_op_expr<LL, LR, LOp>, R, binary_op::geq> operator>=(binary_op_expr<LL, LR, LOp> const & lhs, R const & rhs)
{
	return binary_op_expr<binary_op_expr<LL, LR, LOp>, R, binary_op::geq>(lhs, rhs);
}

} // namespace detail
} // namespace mutest

#endif // CPPMUTEST_DETAIL_CHECK_H
