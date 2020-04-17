#pragma once
// CGL_Ray.h

#include "CGL_Vector3D.h"
#include <string>

using namespace CGL_Math;

namespace CGL_Math
{
	namespace CGL_Values
	{
		class CGL_Ray
		{
		public:
			CGL_Ray(CGL_Vector3D _Position, CGL_Vector3D _Direction);
			
			CGL_Vector3D Position;
			CGL_Vector3D Direction;

			//CGL_Ray Clone();
			std::string ToString();
		};
	}
}