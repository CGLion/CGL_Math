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
		static double Sum(std::vector<double>& list);

		/**
		* Returns the sum of the list elements absolute values:
		*/
		static double SumAbs(std::vector<double>& list);

		/**
		* Converts the list of values to a normalized weight list (sum of 1.0):
		* Counts on user context to provide only positive values.
		*/
		static void ValsToWeights(std::vector<double>& list);

		/**
		* Converts the list of values to a normalized weight list (sum of 1.0):
		* Uses absolute values.
		*/
		static void ValsToWeightsSafe(std::vector<double>& list);

		/**
		* Sorts the vector 'indices' according to ascending order of the elements in the vector 'list'
		*/
		static void ValsToSortedIndicesAscending(const std::vector<double>& list, std::vector<uint_fast16_t>& indices);

		/**
		* Sorts the vector 'indices' according to descending order of the elements in the vector 'list'
		*/
		static void ValsToSortedIndicesDescending(const std::vector<double>& list, std::vector<uint_fast16_t>& indices);
	};
}


