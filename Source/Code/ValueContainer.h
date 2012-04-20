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

	void SetSingle(T value)
	{
		_mode = Single;
		_begin = value;
		_end = value;
	}

	void SetRange(T begin, T end)
	{
		_mode = Range;
		_begin = begin;
		_end = end;
	}

	void SetAny()
	{
		_mode = Any;
	}

	void SetNone()
	{
		_mode = None;
	}

	Mode getMode() { return _mode; }
	T getValue() { return _begin; }
	T getBegin() { return _begin; }
	T getEnd() { return _end; }

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