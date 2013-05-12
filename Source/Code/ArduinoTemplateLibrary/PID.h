/*  
	Arduino Template Library http://atl.codeplex.com
	Written by Marc Jacobi
	Copyright 2012-2013 All Rights Reserved

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

#ifndef __PID_H__
#define __PID_H__

namespace ATL {
namespace Process {

/*
	BaseT is used as a base class and implements:
		T getFeedback()
		unsigned int getDeltaTime()
		T getSmallestAcceptableError()

	T is the data type that hold the values. Either float or double.

Algorithm:
	Error = SetPoint - Feedback
	P = Error * gainP
	I = Sum(previous-I's) + ((Error * deltaTime) * gainI)
	D = (previous-Error / deltaTime) * gainD

	PI = P + I
	PD = P + D
	PID = P + I + D
*/
template<class BaseT, typename T>
class PID : public BaseT
{
public:
	T P(T setPoint, T gainP)
	{
		T input = BaseT::getFeedback();
		T error = CalcError(setPoint, input);

		return CalcP(error, gainP);
	}	

	T P_D(T setPoint, T gainP, T gainD)
	{
		T input = BaseT::getFeedback();
		T error = CalcError(setPoint, input);
		unsigned int deltaTime = BaseT::getDeltaTime();

		return CalcP(error, gainP) + CalcD(error, deltaTime, gainD);
	}

	T P_I(T setPoint, T gainP, T gainI)
	{
		T input = BaseT::getFeedback();
		T error = CalcError(setPoint, input);
		unsigned int deltaTime = BaseT::getDeltaTime();

		return CalcP(error, gainP) + CalcI(error, deltaTime, gainI);
	}

	T P_I_D(T setPoint, T gainP, T gainI, T gainD)
	{
		T input = BaseT::getFeedback();
		T error = CalcError(setPoint, input);
		unsigned int deltaTime = BaseT::getDeltaTime();

		return CalcP(error, gainP) + CalcI(error, deltaTime, gainI) + CalcD(error, deltaTime, gainD);
	}

private:
	T _integralAcc;
	T _lastError;

	inline T CalcError(T setPoint, T input)
	{
		T error = setPoint - input;

		if (error < BaseT::getSmallestAcceptableError() && error > 0 ||
			error > -BaseT::getSmallestAcceptableError() && error < 0)
		{
			error = 0;
		}

		return error;
	}

	inline T CalcP(T error, T gain)
	{
		return error * gain;
	}

	inline T CalcI(T error, unsigned int deltaTime, T gain)
	{
		_integralAcc += (error * deltaTime) * gain;

		return _integralAcc;
	}

	inline T CalcD(T error, unsigned int deltaTime, T gain)
	{
		T value = ((_lastError - error) / deltaTime) * gain;

		_lastError = error;

		return value;
	}
};

}} // ATL.Process

#endif //__PID_H__