#ifndef CPPMUTEST_MUTEST_DETAIL_BINARY_OP_H
#define CPPMUTEST_MUTEST_DETAIL_BINARY_OP_H

namespace mutest {
namespace detail {

enum class binary_op { lshift, rshift, band, bor, bxor, land, lor, eq, neq, lt, leq, gt, geq };

template <binary_op Op>
struct binary_op_eval;

template <>
struct binary_op_eval<binary_op::lshift>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs << rhs) { return lhs << rhs; }
	static char const * text() { return "<<"; }
};

template <>
struct binary_op_eval<binary_op::rshift>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs >> rhs) { return lhs >> rhs; }
	static char const * text() { return ">>"; }
};

template <>
struct binary_op_eval<binary_op::band>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs & rhs) { return lhs & rhs; }
	static char const * text() { return "&"; }
};

template <>
struct binary_op_eval<binary_op::bor>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs | rhs) { return lhs | rhs; }
	static char const * text() { return "|"; }
};

template <>
struct binary_op_eval<binary_op::bxor>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs ^ rhs) { return lhs ^ rhs; }
	static char const * text() { return "^"; }
};

template <>
struct binary_op_eval<binary_op::land>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs && rhs) { return lhs && rhs; }
	static char const * text() { return "&&"; }
};

template <>
struct binary_op_eval<binary_op::lor>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs || rhs) { return lhs || rhs; }
	static char const * text() { return "||"; }
};

template <>
struct binary_op_eval<binary_op::eq>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs == rhs) { return lhs == rhs; }
	static char const * text() { return "=="; }
};

template <>
struct binary_op_eval<binary_op::neq>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs != rhs) { return lhs != rhs; }
	static char const * text() { return "!="; }
};

template <>
struct binary_op_eval<binary_op::lt>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs < rhs) { return lhs < rhs; }
	static char const * text() { return "<"; }
};

template <>
struct binary_op_eval<binary_op::leq>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs <= rhs) { return lhs <= rhs; }
	static char const * text() { return "<="; }
};

template <>
struct binary_op_eval<binary_op::gt>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs > rhs) { return lhs > rhs; }
	static char const * text() { return ">"; }
};

template <>
struct binary_op_eval<binary_op::geq>
{
	template <typename L, typename R>
	static auto eval(L && lhs, R && rhs) -> decltype(lhs >= rhs) { return lhs >= rhs; }
	static char const * text() { return ">="; }
};

} // namespace detail
} // namespace mutest

#endif // CPPMUTEST_MUTEST_DETAIL_BINARY_OP_H
