#ifndef CPPUTEST_TEST_H
#define CPPUTEST_TEST_H

#include "utest.h"

#define TEST UTEST_TEST
#define chk UTEST_CHECK
#define chk_exc(E, f) UTEST_CHECK_EXC(E, f)

#endif // CPPUTEST_TEST_H
