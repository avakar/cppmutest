#ifndef CPPUTEST_UTEST_H
#define CPPUTEST_UTEST_H

#define UTEST_TEST(suite_name, test_name, ...) \
	void suite_name ## _ ## test_name ## _utest(); \
	static ::utest::global_registrar _utest_global_registrar_ ## suite_name ## test_name(#suite_name, #test_name, ::utest::parse_tags(__VA_ARGS__), suite_name ## _ ## test_name ## _utest); \
	void suite_name ## _ ## test_name ## _utest()

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
	test(char const * suite_name, char const * case_name, std::vector<std::string> && tags, test_fn fn)
		: m_suite_name(suite_name), m_case_name(case_name), m_tags(std::move(tags)), m_fn(fn)
	{
	}

	std::string suite_name() const;
	std::string case_name() const;
	std::vector<std::string> const & tags() const { return m_tags; }
	test_fn fn() const { return m_fn; }

private:
	std::string m_suite_name;
	std::string m_case_name;
	std::vector<std::string> m_tags;
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
	global_registrar(char const * suite_name, char const * case_name, std::vector<std::string> && tags, test_fn fn);
	global_registrar * next() const;
	test get_test() const;

	static global_registrar * head();
	static std::vector<test> get_tests();

private:
	global_registrar * m_next;
	char const * m_suite_name;
	char const * m_case_name;
	std::vector<std::string> m_tags;
	test_fn m_fn;
};

std::vector<std::string> parse_tags(char const * tags = 0);

} // utest

#endif // CPPUTEST_UTEST_H
