#ifndef CPPMUTEST_MUTEST_DETAIL_REPR_H
#define CPPMUTEST_MUTEST_DETAIL_REPR_H

#include "char_stream.h"

namespace mutest {
namespace detail {

void repr(char_stream & s, bool v);
void repr(char_stream & s, char v);
void repr(char_stream & s, char const * v);
void repr(char_stream & s, signed char v);
void repr(char_stream & s, signed short v);
void repr(char_stream & s, signed int v);
void repr(char_stream & s, signed long v);
void repr(char_stream & s, signed long long v);
void repr(char_stream & s, unsigned char v);
void repr(char_stream & s, unsigned short v);
void repr(char_stream & s, unsigned int v);
void repr(char_stream & s, unsigned long v);
void repr(char_stream & s, unsigned long long v);

template <typename T>
void repr(char_stream & s, T *)
{
	s.append("<ptr>");
}

template <typename T>
void repr(char_stream & s, T const &)
{
	s.append("<value>");
}

} // namespace detail
} // namespace mutest

#endif // CPPMUTEST_MUTEST_DETAIL_REPR_H
