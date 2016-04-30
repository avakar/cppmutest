#ifndef CPPMUTEST_CHECK_H
#define CPPMUTEST_CHECK_H

#include "detail/check.h"

#define UTEST_CHECK ::utest::detail::check_proxy(__FILE__, __LINE__),

#endif // CPPMUTEST_CHECK_H
