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

#ifndef __PID_H__
#define __PID_H__

namespace ATL {


    /** Implements a Proportional-Integral-Differential controller.
     *  Algorithm:
     *  Error = SetPoint - Feedback
     *  P = Error * biasP
     *  I = Sum(previous-I's) + ((Error * deltaTime) * biasI)
     *  D = (previous-Error / deltaTime) * biasD
     *  P = Proportional of Error
     *  I = Integral over time of Error
     *  D = Derivative over time of Error (dampening)
     *  PI = P + I
     *  PD = P - D
     *  PID = P + I - D
     *  \remarks LowPassFilter:
     *  Filtered = (1 - filterConstant) * previousFiltered + filterConstant * Unfiltered
     *  Where the filterConstant can be a constant value between 0 and 1 
     *  (filter as a function of the number of samples) or can be 
     *  calculated from an actual time constant (in seconds) by:
     *  filterConstant = deltaTime / (deltaTime + timeConstant)
     *  You want to pick a timeConstant that is faster than the expected time 
     *  for the physical input to be changing, but longer than a few samples.
     *  If you don't want to implement the LowPassFilter just return the parameter value:
     *  Filtered = Unfiltered
     *  \tparam BaseT is used as a base class and implements:
     *  `T getFeedback()` Returns the input value.
     *  `T getLargestAcceptableError()` Returns the largest error value.
     *  `T LowPassFilter(T, unsigned int)` Returns a filtered value.
     *  `uint16_t getDeltaTime()` Returns the delta time elapsed between calls to Process.
     *  `void ClipValue(T&)` Adjusts the value to fall within a Range.
     *  \tparam T is the data type that hold the values. Either float, double, int or long?.
     */
    template<class BaseT, typename T>
    class PID : public BaseT
    {
    public:
        /** Performs the actual calculation.
         *  Pass a bias of 0 for unused terms.
         *  \param setPoint is the target value.
         *  \param biasP
         *  \param biasI 
         *  \param biasD
         *  \return Returns the calculated value.
         */
        T Process(const T setPoint, const T biasP, const T biasI, const T biasD)
        {
            T input = BaseT::getFeedback();
            T error = CalcError(setPoint, input);
            uint16_t deltaTime = BaseT::getDeltaTime();

            T value = CalcP(error, biasP) + CalcI(error, deltaTime, biasI) + CalcD(error, deltaTime, biasD);

            BaseT::ClipValue(value);

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

        inline T CalcI(const T error, const uint16_t deltaTime, const T bias)
        {
            if (bias != 0)
            {
                _integralAcc += (error * deltaTime) * bias;

                BaseT::ClipValue(_integralAcc);
            }

            return _integralAcc;
        }

        inline T CalcD(T error, const uint16_t deltaTime, const T bias)
        {
            T value = 0;

            // remove noise from error value
            error = BaseT::LowPassFilter(error, deltaTime);

            if (bias != 0)
            {
                value = ((error - _lastError) * bias) / deltaTime;
            }

            _lastError = error;

            return value;
        }

        /*inline void ClipValue(T& value)
        {
            T maxValue = BaseT::getMaximumValue();
            T minValue = BaseT::getMinimumValue();

            if (value > maxValue)
            {
                value = maxValue;
            }

            if (value < minValue)
            {
                value = minValue;
            }
        }*/
    };

} // ATL

#endif //__PID_H__