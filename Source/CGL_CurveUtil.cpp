#include "CGL_CurveUtil.h"
#include <math.h>

using namespace CGL_Math::CGL_Curves;

int CGL_CurveUtil::NumSamples(int _Precision)
{
	int Num = 2;
	for (int i = 0; i <= _Precision; i++)
	{
		Num += ( int )( pow(2, i) );
	}
	return Num;
}
