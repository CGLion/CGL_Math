#pragma once

#include <vector>

namespace CGL_Math
{
	class CGL_MathUtil
	{
	public:
		/**
		* Returns true if the supplied number is an integer
		*/
		static bool CheckInt(double _Number);

		/**
		* Returns the sum of the list elements: 
		*/
		static double ListSum(std::vector<double>& list);

		/**
		* Returns the sum of the list elements absolute values:
		*/
		static double ListSumAbs(std::vector<double>& list);

		/**
		* Converts the list of values to a normalized weight list (sum of 1.0):
		* Uses absolute values.
		*/
		static void ListValsToWeights(std::vector<double>& list);
	};
}


