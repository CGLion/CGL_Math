#pragma once
#include "CGL_Matrix3D.h"
//

namespace CGL_Math
{
	namespace CGL_Surfaces
	{
		class CGL_CubicBezierPath3DSurfaceKnot : public CGL_Matrix3D
		{
		private:



		public:
			CGL_CubicBezierPath3DSurfaceKnot(double _ForwardTangent = 10.0f, double _BackwardTangent = 10.0f);
			~CGL_CubicBezierPath3DSurfaceKnot();

			double ForwardTangent;
			double BackwardTangent;

			const CGL_Vector3D GetWorldSpaceForwardTangent();
			const CGL_Vector3D GetWorldSpaceBackwardTangent();

			void SetForwardTangent(double _ForwardTangent);
			void SetBackwardTangent(double _BackwardTangent);

			const CGL_Ray GetForwardTangent();
			const CGL_Ray GetBackwardTangent();
		};
	}
}





