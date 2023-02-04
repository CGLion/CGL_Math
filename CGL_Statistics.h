#pragma once

#include <vector>

namespace CGL_Math
{
	class CGL_Statistics
	{
	public:
		static uint_fast32_t medianIndex(std::vector<double>& numList);

		static double median(std::vector<double>& numList);
	};
}
