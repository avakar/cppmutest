#ifndef CPPMUTEST_MUTEST_DETAIL_REGISTRY_H
#define CPPMUTEST_MUTEST_DETAIL_REGISTRY_H

#include "list.h"

namespace utest {

typedef void (test_fn_t)();

struct test_list_entry
	: list_node<test_list_entry>
{
	char const * name;
	test_fn_t * fn;
	char const * file;
	int line;
};

class global_registrar
{
public:
	global_registrar(char const * test_name, test_fn_t * fn, char const * file, int line);
	static list_node<test_list_entry> * head();

private:
	test_list_entry m_node;
};

}

#endif // CPPMUTEST_MUTEST_DETAIL_REGISTRY_H
