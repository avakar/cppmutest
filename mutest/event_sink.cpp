#include "event_sink.h"
#include <assert.h>

static mutest::event_sink * g_global_event_sink = nullptr;

mutest::event_sink_guard::event_sink_guard(event_sink & sink)
{
	assert(g_global_event_sink == nullptr);
	g_global_event_sink = &sink;
}

mutest::event_sink_guard::~event_sink_guard()
{
	g_global_event_sink = nullptr;
}

mutest::event_sink & mutest::global_event_sink()
{
	assert(g_global_event_sink != nullptr);
	return *g_global_event_sink;
}
