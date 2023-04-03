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
			size_t i = x / 8;  // xӳ�䵽��i��char��
			size_t j = x % 8;  // xӳ�䵽��i��char�ϵĵ�j������λ

			_bits[i] |= (1 << j);  // ����i��char�ĵ�j������λ��1
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
			// xһ�ζ�û���ֹ�
			if (!_bs1.test(x) && !_bs2.test(x))
			{
				_bs2.set(x);
			}
			// x���ֹ�һ��
			else if (!_bs1.test(x) && _bs2.test(x))
			{
				_bs1.set(x);
				_bs2.reset(x);
			}
			// x���ֹ�һ�����ϣ������д���
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