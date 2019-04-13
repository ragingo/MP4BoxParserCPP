#pragma once

namespace ragii { namespace math {

	template<typename T>
	constexpr T add(T a, T b)
	{
		return a + b;
	}

	template<typename T>
	constexpr T sub(T a, T b)
	{
		return a - b;
	}

	template<typename T>
	constexpr T mul(T a, T b)
	{
		return a * b;
	}

	template<typename T>
	constexpr T div(T a, T b)
	{
		return a / b;
	}

	template<typename T>
	constexpr T abs(T x)
	{
		return x >= T(0) ? x : -x;
	}

	template<typename T>
	constexpr T pow(T x, T e)
	{
		return e > T(0) ? x * pow<T>(x, e - T(1)) : T(0);
	}

	template<typename T>
	constexpr T fact(T x)
	{
		return x > T(0) ? x * fact(x - 1) : 1;
	}

} }
