#pragma once

#include <iostream>
#include <vector>
using namespace std;

namespace myBitset
{
	template<size_t N>
	class bitset
	{
	public:
		bitset()
		{
			_bits.resize(N / 8 + 1, 0);
		}

		void set(size_t x)
		{
			size_t i = x / 8;  // x映射到第i个char上
			size_t j = x % 8;  // x映射到第i个char上的第j个比特位

			_bits[i] |= (1 << j);  // 将第i个char的第j个比特位置1
		}

		void reset(size_t x)
		{
			size_t i = x / 8;
			size_t j = x % 8;

			_bits[i] &= (~(1 << j));
		}

		bool test(size_t x)
		{
			size_t i = x / 8;
			size_t j = x % 8;

			return _bits[i] & (1 << j);
		}

	private:
		vector<char> _bits;
	};

	template<size_t N>
	class twoBitSet
	{
	public:
		void set(size_t x)
		{
			// x一次都没出现过
			if (!_bs1.test(x) && !_bs2.test(x))
			{
				_bs2.set(x);
			}
			// x出现过一次
			else if (!_bs1.test(x) && _bs2.test(x))
			{
				_bs1.set(x);
				_bs2.reset(x);
			}
			// x出现过一次以上，不进行处理
		}

		void PrintOnce()
		{
			for (int i = 0; i <= N; ++i)
			{
				if (!_bs1.test(i) && _bs2.test(i))
				{
					cout << i << endl;
				}
			}
		}

	private:
		myBitset::bitset<N> _bs1;
		myBitset::bitset<N> _bs2;
	};
}