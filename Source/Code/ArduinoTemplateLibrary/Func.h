/*  
	Arduino Template Library https://github.com/obiwanjacobi/atl
	Written by Marc Jacobi
	Copyright 2012-2015 All Rights Reserved

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __FUNC_H__
#define __FUNC_H__

namespace ATL {

/*
	ReturnT Func()
	ReturnT Func1(Arg1T)
	ReturnT Func2(Arg1T, Arg2T)
	ReturnT Func3(Arg1T, Arg2T, Arg3T)
	ReturnT Func4(Arg1T, Arg2T, Arg3T, Arg4T)
	ReturnT Func5(Arg1T, Arg2T, Arg3T, Arg4T, Arg5T)
	
	void Func0()
	void Func01(Arg1T)
	void Func01(Arg1T, Arg2T)
	void Func03(Arg1T, Arg2T, Arg3T)
	void Func04(Arg1T, Arg2T, Arg3T, Arg4T)
	void Func05(Arg1T, Arg2T, Arg3T, Arg4T, Arg5T)
*/

template<typename ReturnT, ReturnT (*Callback)()>
class Func
{
public:
	ReturnT StaticInvoke()
	{
		return Callback();
	}

	static ReturnT Invoke()
	{
		return Callback();
	}
};

template<typename Arg1T, typename ReturnT, ReturnT (*Callback)(Arg1T)>
class Func1
{
public:
	ReturnT StaticInvoke(Arg1T arg1)
	{
		return Callback(arg1);
	}

	static ReturnT Invoke(Arg1T arg1)
	{
		return Callback(arg1);
	}
};

template<typename Arg1T, typename Arg2T, typename ReturnT, ReturnT (*Callback)(Arg1T, Arg2T)>
class Func2
{
public:
	ReturnT StaticInvoke(Arg1T arg1, Arg2T arg2)
	{
		return Callback(arg1, arg2);
	}

	static ReturnT Invoke(Arg1T arg1, Arg2T arg2)
	{
		return Callback(arg1, arg2);
	}
};

template<typename Arg1T, typename Arg2T, typename Arg3T, typename ReturnT, ReturnT (*Callback)(Arg1T, Arg2T, Arg3T)>
class Func3
{
public:
	ReturnT StaticInvoke(Arg1T arg1, Arg2T arg2, Arg3T arg3)
	{
		return Callback(arg1, arg2, arg3);
	}

	static ReturnT Invoke(Arg1T arg1, Arg2T arg2, Arg3T arg3)
	{
		return Callback(arg1, arg2, arg3);
	}
};

template<typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T, typename ReturnT, ReturnT (*Callback)(Arg1T, Arg2T, Arg3T, Arg4T)>
class Func4
{
public:
	ReturnT StaticInvoke(Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4)
	{
		return Callback(arg1, arg2, arg3, arg4);
	}

	static ReturnT Invoke(Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4)
	{
		return Callback(arg1, arg2, arg3, arg4);
	}
};

template<typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T, typename Arg5T, typename ReturnT, ReturnT (*Callback)(Arg1T, Arg2T, Arg3T, Arg4T, Arg5T)>
class Func5
{
public:
	ReturnT StaticInvoke(Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4, Arg5T arg5)
	{
		return Callback(arg1, arg2, arg3, arg4, arg5);
	}

	static ReturnT Invoke(Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4, Arg5T arg5)
	{
		return Callback(arg1, arg2, arg3, arg4, arg5);
	}
};


//-------------------------------------------------------------------------------------------------

template<void (*Callback)()>
class Func0
{
public:
	void StaticInvoke()
	{
		Callback();
	}

	static void Invoke()
	{
		Callback();
	}
};


template<typename Arg1T, void (*Callback)(Arg1T)>
class Func01
{
public:
	void StaticInvoke(Arg1T arg1)
	{
		Callback(arg1);
	}

	static void Invoke(Arg1T arg1)
	{
		Callback(arg1);
	}
};

template<typename Arg1T, typename Arg2T, void(*Callback)(Arg1T, Arg2T)>
class Func02
{
public:
	void StaticInvoke(Arg1T arg1, Arg2T arg2)
	{
		Callback(arg1, arg2);
	}

	static void Invoke(Arg1T arg1, Arg2T arg2)
	{
		Callback(arg1, arg2);
	}
};

template<typename Arg1T, typename Arg2T, typename Arg3T, void(*Callback)(Arg1T, Arg2T, Arg3T)>
class Func03
{
public:
	void StaticInvoke(Arg1T arg1, Arg2T arg2, Arg3T arg3)
	{
		Callback(arg1, arg2, arg3);
	}

	static void Invoke(Arg1T arg1, Arg2T arg2, Arg3T arg3)
	{
		Callback(arg1, arg2, arg3);
	}
};

template<typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T, void(*Callback)(Arg1T, Arg2T, Arg3T, Arg4T)>
class Func04
{
public:
	void StaticInvoke(Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4)
	{
		Callback(arg1, arg2, arg3, arg4);
	}

	static void Invoke(Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4)
	{
		Callback(arg1, arg2, arg3, arg4);
	}
};

template<typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T, typename Arg5T, void(*Callback)(Arg1T, Arg2T, Arg3T, Arg4T, Arg5T)>
class Func05
{
public:
	void StaticInvoke(Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4, Arg5T arg5)
	{
		Callback(arg1, arg2, arg3, arg4, arg5);
	}

	static void Invoke(Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4, Arg5T arg5)
	{
		Callback(arg1, arg2, arg3, arg4, arg5);
	}
};


} // ATL

#endif //__FUNC_H__