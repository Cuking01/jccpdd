#pragma once



template<typename T>
struct Bits
{
	struct Iterator
	{
		T x;
		int operator*()
		{
			return __builtin_ctz(x);
		}
		bool operator!=(const Iterator&b) const
		{
			return x!=b.x;
		}
		Iterator& operator++()
		{
			x^=x&(-x);
			return *this;
		}
	};
	T x;
	Bits(T x):x(x) {}
	Iterator begin() const
	{
		return {x};
	}

	Iterator end() const
	{
		return {0};
	}
};
