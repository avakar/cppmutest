#include "registry.h"

static mutest::list_node<mutest::test_list_entry> g_test_list_head = { &g_test_list_head, &g_test_list_head };

mutest::global_registrar::global_registrar(char const * test_name, mutest::test_fn_t * fn, char const * file, int line)
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

mutest::list_node<mutest::test_list_entry> & mutest::global_registrar::head()
{
	return g_test_list_head;
}
