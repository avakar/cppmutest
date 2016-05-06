#ifndef CPPMUTEST_EVENT_SINK_H
#define CPPMUTEST_EVENT_SINK_H

namespace utest {

struct event_sink
{
	virtual void fail(char const * file, int line, char const * msg) = 0;
};

struct event_sink_guard
{
	explicit event_sink_guard(event_sink & sink);
	~event_sink_guard();
	event_sink_guard(event_sink_guard const &) = delete;
	event_sink_guard & operator=(event_sink_guard const &) = delete;
};

event_sink & global_event_sink();

}

#endif // CPPMUTEST_EVENT_SINK_H
