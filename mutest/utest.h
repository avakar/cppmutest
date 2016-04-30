#ifndef CPPUTEST_UTEST_H
#define CPPUTEST_UTEST_H

#include "detail/check.h"

#define UTEST_CHECK ::utest::detail::check_proxy(__FILE__, __LINE__),

#define UTEST_TEST(test_name) UTEST_TEST_IMPL(test_name, __COUNTER__)
#define UTEST_TEST_IMPL(test_name, counter) UTEST_TEST_IMPL2(test_name, counter)
#define UTEST_TEST_IMPL2(test_name, counter) \
	static void _utest_test_ ## counter(); \
	static ::utest::global_registrar _utest_global_registrar_ ## counter(test_name, &_utest_test_ ## counter); \
	static void _utest_test_ ## counter()

#include <vector>
#include <string>

namespace utest {

int master_main(int argc, char const * const argv[]);

typedef void (*test_fn)();

class test
{
public:
	test(char const * test_name, test_fn fn)
		: m_test_name(test_name), m_fn(fn)
	{
	}

	std::string test_name() const;
	test_fn fn() const { return m_fn; }

private:
	std::string m_test_name;
	test_fn m_fn;
};

class test_registry
{
public:
	void add(test && t)
	{
		m_tests.push_back(std::move(t));
	}

	std::vector<test> const & tests() const
	{
		return m_tests;
	}

private:
	std::vector<test> m_tests;
};

class global_registrar
{
public:
	global_registrar(char const * test_name, test_fn fn);
	global_registrar * next() const;
	test get_test() const;

	static global_registrar * head();
	static std::vector<test> get_tests();

private:
	global_registrar * m_next;
	char const * m_test_name;
	test_fn m_fn;
};

std::vector<std::string> parse_tags(char const * tags = 0);

} // utest

#endif // CPPUTEST_UTEST_H
