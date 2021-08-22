#include "CGL_MathUtil.h"
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

namespace CGL_Math
{
	bool CGL_MathUtil::CheckInt(double _Number)
	{
		return (_Number - std::floor(_Number) == 0.0) ? true : false;
	}

	double CGL_MathUtil::Sum(std::vector<double>& list)
	{
		double sum = 0.0;
		for (auto& n : list)
		{
			sum += n;
		}
		return sum;
	}

	double CGL_MathUtil::SumAbs(std::vector<double>& list)
	{
		double sum = 0.0;
		for (auto& n : list)
		{
			sum += std::abs(n);
		}
		return sum;
	}
	
	void CGL_MathUtil::ValsToWeights(std::vector<double>& list)
	{
		double mult = 1 / CGL_MathUtil::Sum(list);
		for (auto& n : list)
		{
			 n = n * mult;
		}
	}

	void CGL_MathUtil::ValsToWeightsSafe(std::vector<double>& list)
	{
		double mult = 1 / CGL_MathUtil::SumAbs(list);
		for (auto& n : list)
		{
			n = n * mult;
		}
	}

	void CGL_MathUtil::ValsToSortedIndicesAscending(const std::vector<double>& list, std::vector<uint_fast16_t>& indices)
	{
		for (uint_fast16_t i = 0; i < list.size(); i++)
		{
			indices[i] = i;
		}
		auto comparison = [&list](int a, int b) { return list[a] < list[b]; };
		std::sort(indices.begin(), indices.end(), comparison);
	}

	void CGL_MathUtil::ValsToSortedIndicesDescending(const std::vector<double>& list, std::vector<uint_fast16_t>& indices)
	{
		for (uint_fast16_t i = 0; i < list.size(); i++)
		{
			indices[i] = i;
		}
		auto comparison = [&list](int a, int b) { return list[a] > list[b]; };
		std::sort(indices.begin(), indices.end(), comparison);
	}
}
