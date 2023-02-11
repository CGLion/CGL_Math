#include "CGL_KDTree.h"
#include <vector>

#pragma once

namespace CGL_Math
{
	namespace CGL_Structures
	{
		class CGL_PointCloud
		{
		private:
			uint_fast32_t size;
			std::vector<std::vector<double>> data;
			std::vector<std::vector<uint_fast32_t>> sorted;

			CGL_Structures::CGL_KDTree KDTree;
		};
	}
	
}
