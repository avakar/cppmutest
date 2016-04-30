#include "utest.h"

static utest::list_node<utest::test_list_entry> g_test_list_head = { &g_test_list_head, &g_test_list_head };

utest::global_registrar::global_registrar(char const * test_name, utest::test_fn_t * fn, char const * file, int line)
{
	m_node.name = test_name;
	m_node.fn = fn;
	m_node.file = file;
	m_node.line = line;

	m_node.next = &g_test_list_head;
	m_node.prev = g_test_list_head.prev;
	m_node.next->prev = &m_node;
	m_node.prev->next = &m_node;
}

utest::list_node<utest::test_list_entry> * utest::global_registrar::head()
{
	return &g_test_list_head;
}
