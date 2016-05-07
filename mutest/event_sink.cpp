#include "event_sink.h"
#include <assert.h>

static mutest::exec_env g_global_exec_env = {};

mutest::exec_env & mutest::global_exec_env()
{
	return g_global_exec_env;
}
