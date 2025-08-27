#pragma once



template<typename T>
struct Bits
{
	struct Iterator
	{
		T x;

		static int ctz(T x)
		{
			if constexpr(sizeof(T)==16)
			{
				u3 l=x&u3(-1);
				if(l)return __builtin_ctzll(l);

				return 64+__builtin_ctzll(x>>64);
				
			}
			else if constexpr(sizeof(T)==8)
			{
				return __builtin_ctzll(x);
			}
			else
			{
				return __builtin_ctz(x);
			}
		}

		int operator*() const
		{
			return ctz(x);
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

	int size() const
	{
		if constexpr(sizeof(T)==16)
		{
			return __builtin_popcountll(x>>64)+__builtin_popcountll(x);
			
		}
		else if constexpr(sizeof(T)==8)
		{
			return __builtin_popcountll(x);
		}
		else
		{
			return __builtin_popcount(x);
		}
	}
	Iterator begin() const
	{
		return {x};
	}

	Iterator end() const
	{
		return {0};
	}
};
