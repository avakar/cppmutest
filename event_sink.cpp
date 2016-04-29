#include "event_sink.h"
#include <assert.h>

static utest::event_sink * g_global_event_sink = nullptr;

utest::event_sink_guard::event_sink_guard(event_sink & sink)
{
	assert(g_global_event_sink == nullptr);
	g_global_event_sink = &sink;
}

utest::event_sink_guard::~event_sink_guard()
{
	g_global_event_sink = nullptr;
}

utest::event_sink & utest::global_event_sink()
{
	assert(g_global_event_sink != nullptr);
	return *g_global_event_sink;
}
