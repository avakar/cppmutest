#ifndef CPPUTEST_UTEST_H
#define CPPUTEST_UTEST_H

#define UTEST_TEST(test_name) UTEST_TEST_IMPL(test_name, __COUNTER__)
#define UTEST_TEST_IMPL(test_name, counter) UTEST_TEST_IMPL2(test_name, counter)
#define UTEST_TEST_IMPL2(test_name, counter) \
	static void _utest_test_ ## counter(); \
	static ::utest::global_registrar _utest_global_registrar_ ## counter(test_name, &_utest_test_ ## counter); \
	static void _utest_test_ ## counter()

#define UTEST_ASSERT_EQ(lhs, rhs) \
	if ((rhs) != (lhs)) throw ::utest::assertion_failed_error();

#define UTEST_ASSERT_TRUE(value) \
	if (!(value)) throw ::utest::assertion_failed_error();

#include <vector>
#include <string>

namespace utest {

int main();

class assertion_failed_error
	: public std::runtime_error
{
public:
	assertion_failed_error()
		: std::runtime_error("utest assertion failed")
	{
	}
};

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
