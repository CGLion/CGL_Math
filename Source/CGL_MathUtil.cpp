#include "CGL_MathUtil.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <float.h>

using namespace std;

namespace CGL_Math
{
	bool CGL_MathUtil::CheckInt(double num)
	{
		return (num - std::floor(num) == 0.0) ? true : false;
	}

	int CGL_MathUtil::GetSign(double num)
	{
		return (num > 0) ? 1 : ((num < 0) ? -1 : 0);
	}

	double CGL_MathUtil::SignedThreshold(double num, double thresh)
	{
		double numSign = (signbit(num) - 0.5) * (-2.0);
		double min = ((numSign - 1.0) * 0.5) * DBL_MAX;
		double max = ((numSign + 1.0) * 0.5) * DBL_MAX;
		return Clamp((num - abs(thresh) * numSign), min, max);
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

	double CGL_MathUtil::Clamp(double num, double minimum, double maximum)
	{
		return std::max(minimum, std::min(num, maximum));
	}

	double CGL_MathUtil::Lerp(double a, double b, double t)
	{
		return ( a * (1.0 - t) ) +  (b * t );
	}
	
	double CGL_MathUtil::MapRange(double num, double sa, double sb, double ta, double tb)
	{
		return ( ( (num - sa) / (sb - sa) ) * (tb - ta) ) + ta;
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


	void CGL_MathUtil::AbsValsToSortedIndicesAscending(const std::vector<double>& list, std::vector<uint_fast16_t>& indices)
	{
		for (uint_fast16_t i = 0; i < list.size(); i++)
		{
			indices[i] = i;
		}
		auto comparison = [&list](int a, int b) { return abs(list[a]) < abs(list[b]); };
		std::sort(indices.begin(), indices.end(), comparison);
	}

	void CGL_MathUtil::AbsValsToSortedIndicesDescending(const std::vector<double>& list, std::vector<uint_fast16_t>& indices)
	{
		for (uint_fast16_t i = 0; i < list.size(); i++)
		{
			indices[i] = i;
		}
		auto comparison = [&list](int a, int b) { return abs(list[a]) > abs(list[b]); };
		std::sort(indices.begin(), indices.end(), comparison);
	}


	void CGL_MathUtil::CombineVectors(const std::vector<CGL_Vector3D>& vectors, const std::vector<double>& weights, CGL_Vector3D& combination)
	{
		combination.X = 0.0;
		combination.Y = 0.0;
		combination.Z = 0.0;
		
		for (uint_fast16_t i = 0 ; i < vectors.size(); i++)
		{
			combination.X += vectors[i].X * weights[i];
			combination.Y += vectors[i].Y * weights[i];
			combination.Z += vectors[i].Z * weights[i];
		}
	}
}
