#ifndef __RANGE_H__
#define __RANGE_H__

namespace ATL {

template<typename T>
class Range
{
public:
	Range(T begin, T end)
	{
		Begin = begin;
		End = end;
	}

	T Begin;
	T End;

	bool IsInRange(T value)
	{
		if (begin > end)
		{
			return (end <= value && value <= begin);
		}

		return (begin <= value && value <= end);
	}

	void Normalize()
	{
		if (begin > end)
		{
			T temp = end;
			end = begin;
			begin = temp;
		}
	}
};

} //ATL

#endif //__RANGE_H__