#include "CGL_MathUtil.h"
#include <cmath>
#include <vector>

using namespace std;

namespace CGL_Math
{
	bool CGL_MathUtil::CheckInt(double _Number)
	{
		return (_Number - std::floor(_Number) == 0.0) ? true : false;
	}

	double CGL_MathUtil::ListSum(std::vector<double>& list)
	{
		double sum = 0.0;
		for (auto& n : list)
		{
			sum += n;
		}
		return sum;
	}

	double CGL_MathUtil::ListSumAbs(std::vector<double>& list)
	{
		double sum = 0.0;
		for (auto& n : list)
		{
			sum += std::abs(n);
		}
		return sum;
	}
	
	void CGL_MathUtil::ListValsToWeights(std::vector<double>& list)
	{
		double sum = CGL_MathUtil::ListSumAbs(list);
		for (auto& n : list)
		{
			 n = n / sum;
		}
	}
}
