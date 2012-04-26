#ifndef __VALUE_H__
#define __VALUE_H__

template <typename T>
class ValueContainer
{
public:
	enum Mode
	{
		None,
		Single,
		Range,
		Any,
	};

	ValueContainer()
	{
		SetNone();
	}

	ValueContainer(T value)
	{
		SetSingle(value);
	}

	ValueContainer(T begin, T end)
	{
		SetRange(begin, end);
	}

	inline void SetSingle(T value)
	{
		_mode = Single;
		_begin = value;
		_end = value;
	}

	inline void SetRange(T begin, T end)
	{
		_mode = Range;
		_begin = begin;
		_end = end;
	}

	inline void SetAny()
	{
		_mode = Any;
	}

	inline void SetNone()
	{
		_mode = None;
	}

	inline Mode getMode() { return _mode; }
	inline T getValue() { return _begin; }
	inline T getBegin() { return _begin; }
	inline T getEnd() { return _end; }

	bool IsInRange(T value)
	{
		if (_mode == None) return false;
		if (_mode == Any) return true;

		if (_begin > _end)
		{
			return (_end <= value && value <= _begin);
		}

		return (_begin <= value && value <= _end);
	}

	void Normalize()
	{
		if (_begin > _end)
		{
			T temp = _end;
			_end = _begin;
			_begin = temp;
		}
	}

private:
	Mode _mode;
	T _begin;
	T _end;
};

#endif //__VALUE_H__