#include "CGL_MathUtil.h"
#include <cmath>

using namespace std;

namespace CGL_Math
{
	bool CGL_MathUtil::CheckInt(double _Number)
	{
		return (_Number - floor(_Number) == 0.0) ? true : false;
	}
}
