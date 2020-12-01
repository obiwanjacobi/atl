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

#ifndef __DELEGATE_H__
#define __DELEGATE_H__

namespace ATL {

/*
	ReturnT Delegate(ClassT)
	ReturnT Delegate1(ClassT, Arg1T)
	ReturnT Delegate2(ClassT, Arg1T, Arg2T)
	ReturnT Delegate3(ClassT, Arg1T, Arg2T, Arg3T)
	ReturnT Delegate4(ClassT, Arg1T, Arg2T, Arg3T, Arg4T)
	ReturnT Delegate5(ClassT, Arg1T, Arg2T, Arg3T, Arg4T, Arg5T)
	
	void Delegate0(ClassT)
	void Delegate01(ClassT, Arg1T)
	void Delegate01(ClassT, Arg1T, Arg2T)
	void Delegate03(ClassT, Arg1T, Arg2T, Arg3T)
	void Delegate04(ClassT, Arg1T, Arg2T, Arg3T, Arg4T)
	void Delegate05(ClassT, Arg1T, Arg2T, Arg3T, Arg4T, Arg5T)
*/

template<class ClassT, typename ReturnT, ReturnT (ClassT::*Callback)()>
class Delegate
{
public:
	Delegate(ClassT* instance)
	{
		Instance = instance;
	}

	ReturnT Invoke()
	{
		return (Instance->*Callback)();
	}

	static ReturnT Invoke(ClassT* instance)
	{
		return (instance->*Callback());
	}

protected:
	ClassT* Instance;
};

template<class ClassT, typename Arg1T, typename ReturnT, ReturnT (ClassT::*Callback)(Arg1T)>
class Delegate1
{
public:
	Delegate1(ClassT* instance)
	{
		Instance = instance;
	}

	ReturnT Invoke(Arg1T arg1)
	{
		return (Instance->*Callback)(arg1);
	}

	static ReturnT Invoke(ClassT* instance, Arg1T arg1)
	{
		return (instance->*Callback)(arg1);
	}

protected:
	ClassT* Instance;
};

template<class ClassT, typename Arg1T, typename Arg2T, typename ReturnT, ReturnT (ClassT::*Callback)(Arg1T, Arg2T)>
class Delegate2
{
public:
	Delegate2(ClassT* instance)
	{
		Instance = instance;
	}

	ReturnT Invoke(Arg1T arg1, Arg2T arg2)
	{
		return (Instance->*Callback)(arg1, arg2);
	}

	static ReturnT Invoke(ClassT* instance, Arg1T arg1, Arg2T arg2)
	{
		return (instance->*Callback)(arg1, arg2);
	}

protected:
	ClassT* Instance;
};

template<class ClassT, typename Arg1T, typename Arg2T, typename Arg3T, typename ReturnT, ReturnT (ClassT::*Callback)(Arg1T, Arg2T, Arg3T)>
class Delegate3
{
public:
	Delegate3(ClassT* instance)
	{
		Instance = instance;
	}

	ReturnT Invoke(Arg1T arg1, Arg2T arg2, Arg3T arg3)
	{
		return (Instance->*Callback)(arg1, arg2, arg3);
	}

	static ReturnT Invoke(ClassT* instance, Arg1T arg1, Arg2T arg2, Arg3T arg3)
	{
		return (instance->*Callback)(arg1, arg2, arg3);
	}

protected:
	ClassT* Instance;
};

template<class ClassT, typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T, typename ReturnT, ReturnT (ClassT::*Callback)(Arg1T, Arg2T, Arg3T, Arg4T)>
class Delegate4
{
public:
	Delegate4(ClassT* instance)
	{
		Instance = instance;
	}

	ReturnT Invoke(Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4)
	{
		return (Instance->*Callback)(arg1, arg2, arg3, arg4);
	}

	static ReturnT Invoke(ClassT* instance, Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4)
	{
		return (instance->*Callback)(arg1, arg2, arg3, arg4);
	}

protected:
	ClassT* Instance;
};

template<class ClassT, typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T, typename Arg5T, typename ReturnT, ReturnT (ClassT::*Callback)(Arg1T, Arg2T, Arg3T, Arg4T, Arg5T)>
class Delegate5
{
public:
	Delegate5(ClassT* instance)
	{
		Instance = instance;
	}

	ReturnT Invoke(Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4, Arg5T arg5)
	{
		return (Instance->*Callback)(arg1, arg2, arg3, arg4, arg5);
	}

	static ReturnT Invoke(ClassT* instance, Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4, Arg5T arg5)
	{
		return (instance->*Callback)(arg1, arg2, arg3, arg4, arg5);
	}

protected:
	ClassT* Instance;
};

//-------------------------------------------------------------------------------------------------

template<class ClassT, void (ClassT::*Callback)()>
class Delegate0
{
public:
	Delegate0(ClassT* instance)
	{
		Instance = instance;
	}

	void Invoke()
	{
		(Instance->*Callback)();
	}

	static void Invoke(ClassT* instance)
	{
		(instance->*Callback)();
	}

protected:
	ClassT* Instance;
};

template<class ClassT, typename Arg1T, void (ClassT::*Callback)(Arg1T)>
class Delegate01
{
public:
	Delegate01(ClassT* instance)
	{
		Instance = instance;
	}

	void Invoke(Arg1T arg1)
	{
		(Instance->*Callback)(arg1);
	}

	static void Invoke(ClassT* instance, Arg1T arg1)
	{
		(instance->*Callback)(arg1);
	}

protected:
	ClassT* Instance;
};

template<class ClassT, typename Arg1T, typename Arg2T, void (ClassT::*Callback)(Arg1T, Arg2T)>
class Delegate02
{
public:
	Delegate02(ClassT* instance)
	{
		Instance = instance;
	}

	void Invoke(Arg1T arg1, Arg2T arg2)
	{
		(Instance->*Callback)(arg1, arg2);
	}

	static void Invoke(ClassT* instance, Arg1T arg1, Arg2T arg2)
	{
		(instance->*Callback)(arg1, arg2);
	}

protected:
	ClassT* Instance;
};

template<class ClassT, typename Arg1T, typename Arg2T, typename Arg3T, void (ClassT::*Callback)(Arg1T, Arg2T, Arg3T)>
class Delegate03
{
public:
	Delegate03(ClassT* instance)
	{
		Instance = instance;
	}

	void Invoke(Arg1T arg1, Arg2T arg2, Arg3T arg3)
	{
		(Instance->*Callback)(arg1, arg2, arg3);
	}

	static void Invoke(ClassT* instance, Arg1T arg1, Arg2T arg2, Arg3T arg3)
	{
		(instance->*Callback)(arg1, arg2, arg3);
	}

protected:
	ClassT* Instance;
};

template<class ClassT, typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T, void (ClassT::*Callback)(Arg1T, Arg2T, Arg3T, Arg4T)>
class Delegate04
{
public:
	Delegate04(ClassT* instance)
	{
		Instance = instance;
	}

	void Invoke(Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4)
	{
		(Instance->*Callback)(arg1, arg2, arg3, arg4);
	}

	static void Invoke(ClassT* instance, Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4)
	{
		(instance->*Callback)(arg1, arg2, arg3, arg4);
	}

protected:
	ClassT* Instance;
};

template<class ClassT, typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T, typename Arg5T, void (ClassT::*Callback)(Arg1T, Arg2T, Arg3T, Arg4T, Arg5T)>
class Delegate05
{
public:
	Delegate05(ClassT* instance)
	{
		Instance = instance;
	}

	void Invoke(Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4, Arg5T arg5)
	{
		(Instance->*Callback)(arg1, arg2, arg3, arg4, arg5);
	}

	static void Invoke(ClassT* instance, Arg1T arg1, Arg2T arg2, Arg3T arg3, Arg4T arg4, Arg5T arg5)
	{
		(instance->*Callback)(arg1, arg2, arg3, arg4, arg5);
	}

protected:
	ClassT* Instance;
};

} // ATL

#endif //__DELEGATE_H__
