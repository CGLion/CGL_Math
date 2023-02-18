#include "CGL_KDTreeNode.h"

#pragma once
namespace CGL_Math
{
	namespace CGL_Structures
	{
		class CGL_KDTree
		{
			CGL_Structures::CGL_KDTreeNode* root;
			uint_fast8_t dims;
			uint_fast32_t size;
			std::vector<std::vector<double>> data;
			std::vector<std::vector<uint_fast32_t>> sorted;
		};
	}
}