#pragma once

// CGL_CurveUtil.h
//
//

namespace CGL_Math
{
	namespace CGL_Curves
	{
		class CGL_CurveUtil
		{
		public:
			
			/**
			Computes the number of curve samples at a given precision value
			*/
			static int NumSamples(int _Precision);
		};
	}
}
