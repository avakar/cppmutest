#include "repr.h"
using namespace mutest::detail;

void mutest::detail::repr(char_stream & s, bool v)
{
	s.append(v? "true": "false");
}

static void escape_char(char_stream & s, char c)
{
	static char const escapes[] = "\nn\rr\tt\\\\\''\"\"";

	char const * p = escapes;
	while (*p)
	{
		if (*p++ == c)
		{
			s.append(*p);
			return;
		}

		++p;
	}

	if (c < 32 || c > 0x7e)
	{
		static char const digits[] = "0123456789abcdef";

		s.append("\\x");
		s.append(digits[(c >> 4) & 0xf]);
		s.append(digits[c & 0xf]);
		return;
	}

	s.append(c);
}

void mutest::detail::repr(char_stream & s, char v)
{
	s.append('\'');
	escape_char(s, v);
	s.append('\'');
}

void mutest::detail::repr(char_stream & s, char const * v)
{
	s.append('"');
	char const * p = v;
	while (*p)
		escape_char(s, *p++);
	s.append('"');
}

void mutest::detail::repr(char_stream & s, signed char v) { repr(s, (long long)v); }
void mutest::detail::repr(char_stream & s, signed short v) { repr(s, (long long)v); }
void mutest::detail::repr(char_stream & s, signed int v) { repr(s, (long long)v); }
void mutest::detail::repr(char_stream & s, signed long v) { repr(s, (long long)v); }
void mutest::detail::repr(char_stream & s, unsigned char v) { repr(s, (unsigned long long)v); }
void mutest::detail::repr(char_stream & s, unsigned short v) { repr(s, (unsigned long long)v); }
void mutest::detail::repr(char_stream & s, unsigned int v) { repr(s, (unsigned long long)v); }
void mutest::detail::repr(char_stream & s, unsigned long v) { repr(s, (unsigned long long)v); }

void mutest::detail::repr(char_stream & s, signed long long v)
{
	if (v < 0)
	{
		s.append('-');
		repr(s, (unsigned long long)-v);
	}
	else
	{
		repr(s, (unsigned long long)v);
	}
}

void mutest::detail::repr(char_stream & s, unsigned long long v)
{
	if (v == 0)
	{
		s.append('0');
		return;
	}

	char buf[3*sizeof v];
	char * ptr = buf;
	while (v)
	{
		static char const digits[] = "0123456789";
		*ptr++ = digits[v % 10];
		v /= 10;
	}

	while (ptr != buf)
		s.append(*--ptr);
}
