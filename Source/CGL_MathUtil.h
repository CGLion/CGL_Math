#pragma once

#include "CGL_Vector3D.h"
#include <vector>

using namespace CGL_Math;
using namespace CGL_Math::CGL_Values;

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
		* Retuns a value no less then 'min'and no greater then 'max'
		*/
		static double Clamp(double val, double min, double max);

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

		/**
		* Combines the supllied 'vectors' using the supplied 'weights and updates the supplied 'combination' vector reference with the resulting vector: 
		*/
		static void CombineVectors(const std::vector<CGL_Vector3D>& vectors, const std::vector<double>& weights, CGL_Vector3D& combination);
	};
}


