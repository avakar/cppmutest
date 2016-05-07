#ifndef CPPMUTEST_EVENT_SINK_H
#define CPPMUTEST_EVENT_SINK_H

namespace mutest {

struct event_sink
{
	virtual void check(bool success, char const * file, int line, char const * msg) = 0;
};

struct exec_env
{
	bool verbose;
	event_sink * sink;
};

exec_env & global_exec_env();

}

#endif // CPPMUTEST_EVENT_SINK_H
