#include "utest.h"

static utest::global_registrar * g_registry_head = 0;

utest::global_registrar::global_registrar(char const * test_name, utest::test_fn fn)
	: m_next(g_registry_head), m_test_name(test_name), m_fn(fn)
{
	g_registry_head = this;
}

utest::global_registrar * utest::global_registrar::next() const
{
	return m_next;
}

utest::global_registrar * utest::global_registrar::head()
{
	return g_registry_head;
}

utest::test utest::global_registrar::get_test() const
{
	return utest::test(m_test_name, m_fn);
}

std::vector<utest::test> utest::global_registrar::get_tests()
{
	std::vector<utest::test> res;

	utest::global_registrar * cur = utest::global_registrar::head();
	for (; cur; cur = cur->next())
		res.push_back(cur->get_test());

	return res;
}
