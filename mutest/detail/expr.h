#ifndef CPPMUTEST_MUTEST_DETAIL_EXPR_H
#define CPPMUTEST_MUTEST_DETAIL_EXPR_H

#include "binary_op.h"

namespace mutest {
namespace detail {

template <typename T>
T declval();

template <typename E>
struct expr
{
	expr(E const & e): e(e) {}
	E e;
};

template <typename T>
struct value_expr
{
	typedef T const & value_type;

	explicit value_expr(T const & value);
	bool check(char_stream & ss, bool verbose) const;
	value_type value() const;

private:
	T const & m_value;
};

template <typename L, typename R, binary_op Op>
struct binary_expr
{
	typedef decltype(binary_op_eval<Op>::eval(declval<typename L::value_type>(), declval<R const &>())) value_type;

	binary_expr(L const & lhs, R const & rhs);
	bool check(char_stream & ss, bool verbose) const;
	value_type value() const;

private:
	L const & m_lhs;
	R const & m_rhs;
};

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::eq>> operator==(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::eq>(lhs.e, rhs);
}

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::neq>> operator!=(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::neq>(lhs.e, rhs);
}

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::lt>> operator<(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::lt>(lhs.e, rhs);
}

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::leq>> operator<=(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::leq>(lhs.e, rhs);
}

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::gt>> operator>(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::gt>(lhs.e, rhs);
}

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::geq>> operator>=(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::geq>(lhs.e, rhs);
}

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::lshift>> operator<<(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::lshift>(lhs.e, rhs);
}

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::rshift>> operator>>(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::rshift>(lhs.e, rhs);
}

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::band>> operator&(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::band>(lhs.e, rhs);
}

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::bor>> operator|(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::bor>(lhs.e, rhs);
}

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::bxor>> operator^(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::bxor>(lhs.e, rhs);
}

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::land>> operator&&(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::land>(lhs.e, rhs);
}

template <typename L, typename R>
expr<binary_expr<L, R, binary_op::lor>> operator||(expr<L> const & lhs, R const & rhs)
{
	return binary_expr<L, R, binary_op::lor>(lhs.e, rhs);
}

template <typename T>
value_expr<T>::value_expr(T const & value)
	: m_value(value)
{
}

template <typename T>
bool value_expr<T>::check(char_stream & ss, bool verbose) const
{
	bool success = static_cast<bool>(m_value);
	if (!success || verbose)
		repr(ss, m_value);
	return success;
}

template <typename T>
T const & value_expr<T>::value() const
{
	return m_value;
}

template <typename L, typename R, binary_op Op>
binary_expr<L, R, Op>::binary_expr(L const & lhs, R const & rhs)
	: m_lhs(lhs), m_rhs(rhs)
{
}

template <typename L, typename R, binary_op Op>
bool binary_expr<L, R, Op>::check(char_stream & ss, bool verbose) const
{
	auto && lhs = m_lhs.value();
	bool res = binary_op_eval<Op>::eval(lhs, m_rhs);
	if (verbose || !res)
	{
		repr(ss, lhs);
		ss.append(' ');
		ss.append(binary_op_eval<Op>::text());
		ss.append(' ');
		repr(ss, m_rhs);
	}
	return res;
}

template <typename L, typename R, binary_op Op>
typename binary_expr<L, R, Op>::value_type binary_expr<L, R, Op>::value() const
{
	return binary_op_eval<Op>::eval(m_lhs.value(), m_rhs);
}

} // namespace detail
} // namespace mutest

#endif // CPPMUTEST_MUTEST_DETAIL_EXPR_H
