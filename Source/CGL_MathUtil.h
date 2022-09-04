#pragma once

#include "CGL_Vector3D.h"
#include <vector>

using namespace CGL_Math;
using namespace CGL_Math::CGL_Values;

namespace CGL_Math
{
	/**
	 * @brief A collection of static math utilities
	 * 
	*/
	class CGL_MathUtil
	{
	public:

		/**
		* PI constant
		*/
		static constexpr double CONST_PI = 3.1415926535897932384626433832795;
		/**
		* PI X 2 constant
		*/
		static constexpr double CONST_PI_2 = 6.283185307179586476925286766559;
		/**
		* PI X 0.5 constant (half PI)
		*/
		static constexpr double CONST_PI_05 = 1.5707963267948966192313216916398;

		/**
		* Returns true if the supplied number represents an integer
		* @param num an input double value  
		*/
		static bool CheckInt(double num);

		/**
		* Returns -1 for negative 0 for 0 and 1 for positive value:
		* Note:
		* If the distinction between 0 and positive isn't requires it's better to use 'signbit()' from cmath
		*/
		static int GetSign(double num);

		/**
		* Retuns a value no less then 'minimum'and no greater then 'maximum'
		*/
		static double Clamp(double val, double minimum, double maximum);

		/**
		* Retuns a linearly interpolated value between a and b at t:
		*/
		static double Lerp(double a, double b, double t);

		/**
		* Retuns the mapped value from source range sa->sb to target range ta->tb
		*/
		static double MapRange(double num, double sa, double sb, double ta, double tb);

		/**
		* Returns the clamped difference between num and thresh or num and -thresh depending on num sign:
		* thresh is used as absolute value
		*/
		static double SignedThreshold(double num, double thresh);

		/**
		* Returns the sum of the list elements: 
		*/
		static double Sum(std::vector<double>& list);

		/**
		* Returns the sum of the list elements absolute values:
		*/
		static double SumAbs(std::vector<double>& list);



		/**
		* Converts the list of values to a normalized weight list (sum of 1.0):
		* Counts on user context to provide only positive values.
		* If the list contains only 0s the weights will be 1 / num of elements
		*/
		static void ValsToWeights(std::vector<double>& list);

		/**
		* Converts the list of values to a normalized weight list (sum of 1.0):
		* Uses absolute values.
		* If the list contains only 0s the weights will be 1 / num of elements
		*/
		static void ValsToWeightsSafe(std::vector<double>& list);

		/**
		* Sorts the vector 'indices' according to ascending order of the element values in the vector 'list'
		*/
		static void ValsToSortedIndicesAscending(const std::vector<double>& list, std::vector<uint_fast16_t>& indices);

		/**
		* Sorts the vector 'indices' according to descending order of the elements values in the vector 'list'
		*/
		static void ValsToSortedIndicesDescending(const std::vector<double>& list, std::vector<uint_fast16_t>& indices);

		/**
		* Sorts the vector 'indices' according to ascending order of the element absolute values in the vector 'list'
		*/
		static void AbsValsToSortedIndicesAscending(const std::vector<double>& list, std::vector<uint_fast16_t>& indices);

		/**
		* Sorts the vector 'indices' according to descending order of the element absolute values in the vector 'list'
		*/
		static void AbsValsToSortedIndicesDescending(const std::vector<double>& list, std::vector<uint_fast16_t>& indices);

		/**
		* Combines the supllied 'vectors' using the supplied 'weights and updates the supplied 'combination' vector reference with the resulting vector: 
		*/
		static void CombineVectors(const std::vector<CGL_Vector3D>& vectors, const std::vector<double>& weights, CGL_Vector3D& combination);

		/**
		* Generate a random double value in range 0.0 -> 1.0
		* This function uses the std rand function internaly without managing the seed
		*/
		static double RandNum();

		/**
		* Generate a random unit vector
		* This function uses instances of std random_device, mt19937 and normal_dostribution
		* Instancing these objects per every call works but better be checked 
		*/
		static CGL_Values::CGL_Vector3D* RandDir3D();
	};
}


