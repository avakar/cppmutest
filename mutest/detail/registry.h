#ifndef CPPMUTEST_MUTEST_DETAIL_REGISTRY_H
#define CPPMUTEST_MUTEST_DETAIL_REGISTRY_H

#include <vector>
#include <string>

namespace utest {

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

}

#endif // CPPMUTEST_MUTEST_DETAIL_REGISTRY_H
