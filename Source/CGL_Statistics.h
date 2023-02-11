#pragma once

#include <vector>

namespace CGL_Math
{
	class CGL_Statistics
	{
	public:
		static std::pair<uint32_t, uint32_t> medianIndex(std::vector<double>& numList);

		static double median(std::vector<double>& numList);
	};
}
