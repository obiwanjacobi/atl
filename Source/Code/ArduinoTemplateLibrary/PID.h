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
		T getMaximumValue()
		T getLargestAcceptableError()
		unsigned int getDeltaTime()
		T LowPassFilter(T)

	T is the data type that hold the values. Either float or double or int or long?.

Algorithm:
	Error = SetPoint - Feedback
	P = Error * biasP
	I = Sum(previous-I's) + ((Error * deltaTime) * biasI)
	D = (previous-Error / deltaTime) * biasD

	P = Proportional of Error
	I = Integral over time of Error
	D = Derivative over time of Error (dampening)

	PI = P + I
	PD = P - D
	PID = P + I - D

LowPassFilter:
	Filtered = (1 - filterConstant) * previousFiltered + filterConstant * Unfiltered

	Where the filterConstant can be a constant value between 0 and 1 
	(filter as a function of the number of samples) or can be 
	calculated from an actual time constant (in seconds) by:

	filterConstant = deltaTime / (deltaTime + timeConstant)

	You want to pick a timeConstant that is faster than the expected time 
	for the physical input to be changing, but longer than a few samples.

	If you don't want to implement the LowPassFilter just return the parameter value:

	Filtered = Unfiltered


*/
template<class BaseT, typename T>
class PID : public BaseT
{
public:
	// pass a bias of 0 for unused terms.
	T Process(const T setPoint, const T biasP, const T biasI, const T biasD)
	{
		T input = BaseT::getFeedback();
		T error = CalcError(setPoint, input);
		unsigned int deltaTime = BaseT::getDeltaTime();

		T value = CalcP(error, biasP) + CalcI(error, deltaTime, biasI) + CalcD(error, deltaTime, biasD);

		ClipValue(value);

		return value;
	}

private:
	T _integralAcc;
	T _lastError;

	inline T CalcError(const T setPoint, const T input)
	{
		T error = setPoint - input;
		T largestError = BaseT::getLargestAcceptableError();

		if (error <= largestError && error >= 0 ||
			error >= -largestError && error <= 0)
		{
			error = 0;
			_integralAcc = 0;
		}

		return error;
	}

	inline T CalcP(const T error, const T bias)
	{
		if (bias == 0) return 0;

		return error * bias;
	}

	inline T CalcI(const T error, const unsigned int deltaTime, const T bias)
	{
		if (bias != 0)
		{
			_integralAcc += (error * deltaTime) * bias;

			ClipValue(_integralAcc);
		}

		return _integralAcc;
	}

	inline T CalcD(const T error, const unsigned int deltaTime, const T bias)
	{
		T value = 0;
		
		// remove noise from error value
		error = BaseT::LowPassFilter(error);

		if (bias != 0)
		{
			value = ((error - _lastError) * bias) / deltaTime;
		}

		_lastError = error;

		return value;
	}

	inline void ClipValue(T& value)
	{
		T maxValue = BaseT::getMaximumValue();

		if (value > maxValue)
		{
			value = maxValue;
		}
	}
};

}} // ATL.Process

#endif //__PID_H__