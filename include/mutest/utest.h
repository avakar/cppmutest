#ifndef CPPUTEST_UTEST_H
#define CPPUTEST_UTEST_H

#include "../../src/detail/check.h"
#include "../../src/detail/registry.h"
#include "../../src/copy_error_tester.h"
#include "../../src/exc_checker.h"

#define UTEST_CHECK ::mutest::detail::check_proxy(__FILE__, __LINE__), ::mutest::detail::init_expr() <<
#define UTEST_TEST(test_name) UTEST_TEST_IMPL(test_name, __COUNTER__)

#define UTEST_TEST_IMPL(test_name, counter) UTEST_TEST_IMPL2(test_name, counter)
#define UTEST_TEST_IMPL2(test_name, counter) \
	static void _utest_test_ ## counter(); \
	static ::mutest::global_registrar _utest_global_registrar_ ## counter(test_name, &_utest_test_ ## counter, __FILE__, __LINE__); \
	static void _utest_test_ ## counter()

#define UTEST_CHECK_EXC(E, stmt) ::mutest::detail::exc_checker<E>::check([&] { stmt; }, __FILE__, __LINE__)

#endif // CPPUTEST_UTEST_H
