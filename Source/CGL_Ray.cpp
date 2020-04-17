#include "CGL_Ray.h"
#include <string>
#include <sstream>

using namespace CGL_Math::CGL_Values;

CGL_Ray::CGL_Ray(CGL_Vector3D _Position, CGL_Vector3D _Direction)
{
	Position = _Position;
	Direction = _Direction;
}

//CGL_Ray CGL_Ray::Clone()
//{
//	return CGL_Ray(Position.Clone(), Direction.Clone());
//}

std::string CGL_Ray::ToString()
{
	std::ostringstream Convert;
	Convert << Position.ToString() << " , " << Direction.ToString();
	return Convert.str();
}
