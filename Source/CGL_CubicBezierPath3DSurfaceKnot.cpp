#include "CGL_CubicBezierPath3DSurfaceKnot.h"

namespace CGL_Math
{
	namespace CGL_Surfaces
	{

		CGL_CubicBezierPath3DSurfaceKnot::CGL_CubicBezierPath3DSurfaceKnot(double _ForwardTangent, double _BackwardTangent)
		{
			ForwardTangent = _ForwardTangent;
			BackwardTangent = _BackwardTangent;
		}


		CGL_CubicBezierPath3DSurfaceKnot::~CGL_CubicBezierPath3DSurfaceKnot()
		{
		}
		const CGL_Vector3D CGL_CubicBezierPath3DSurfaceKnot::GetWorldSpaceForwardTangent()
		{
			return (this->TransformVector(CGL_Vector3D(ForwardTangent, 0.0, 0.0)));
		}
		const CGL_Vector3D CGL_CubicBezierPath3DSurfaceKnot::GetWorldSpaceBackwardTangent()
		{
			return (this->TransformVector(CGL_Vector3D(-BackwardTangent, 0.0, 0.0)));
		}
		void CGL_CubicBezierPath3DSurfaceKnot::SetForwardTangent(double _ForwardTangent)
		{
			ForwardTangent = _ForwardTangent;
		}
		void CGL_CubicBezierPath3DSurfaceKnot::SetBackwardTangent(double _BackwardTangent)
		{
			BackwardTangent = _BackwardTangent;
		}
		const CGL_Ray CGL_CubicBezierPath3DSurfaceKnot::GetForwardTangent()
		{
			CGL_Vector3D Tangent = this->GetYAxis();
			Tangent.ScaleBy(ForwardTangent);
			return CGL_Ray(this->GetPosition(), Tangent);
		}
		const CGL_Ray CGL_CubicBezierPath3DSurfaceKnot::GetBackwardTangent()
		{
			CGL_Vector3D Tangent = this->GetYAxis();
			Tangent.ScaleBy(-BackwardTangent);
			return CGL_Ray(this->GetPosition(), Tangent);
		}
	}
}