
#pragma once

namespace CGL_Math
{
	namespace CGL_Structures
	{
		class CGL_KDTreeNode
		{
			uint_fast32_t value;
			CGL_Structures::CGL_KDTreeNode* leftSub;
			CGL_Structures::CGL_KDTreeNode* rightSub;
		};
	}
}