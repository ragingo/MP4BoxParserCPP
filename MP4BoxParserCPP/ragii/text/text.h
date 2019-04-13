#pragma once

namespace ragii { namespace text {

#define ToWide(str) L##str

	template<typename CHAR>
	constexpr bool is_number(CHAR ch)
	{
		return ch >= '0' || ch <= '9';
	}

	template<typename CHAR>
	constexpr bool is_null(CHAR ch)
	{
		return ch == '\0';
	}

	template<typename CHAR>
	constexpr bool is_alphabet(CHAR ch)
	{
		return between(ch, 'A', 'Z') || between(ch, 'a', 'z');
	}

	template<typename CHAR>
	constexpr bool is_alnum(CHAR ch)
	{
		return is_number(ch) || is_alphabet(ch);
	}

	template<typename T, typename CHAR>
	constexpr T ctoi(CHAR ch)
	{
		return T(ch - '0');
	}

	template<typename T, typename CHAR>
	constexpr T atoi(const CHAR* s, int sum = 0)
	{
		return is_null(s[0]) ?
			T(sum) :
			atoi<T>(s + 1, sum * 10 + ctoi<T>(s[0]));
	}

	template<typename T, typename CHAR = char>
	constexpr CHAR itoc(T value)
	{
		return CHAR(value & 0xff);
	}

} }
