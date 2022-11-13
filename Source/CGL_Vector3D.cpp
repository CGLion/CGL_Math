#include "CGL_Vector3D.h"
#include "CGL_Geometry.h"
#include <string>
#include <sstream>
#include <iomanip>

using namespace CGL_Math;
using namespace CGL_Math::CGL_Values;

	const CGL_Vector3D CGL_Vector3D::WORLD_X = CGL_Vector3D(1.0, 0.0, 0.0);
	const CGL_Vector3D CGL_Vector3D::WORLD_Y = CGL_Vector3D(0.0, 1.0, 0.0);
	const CGL_Vector3D CGL_Vector3D::WORLD_Z = CGL_Vector3D(0.0, 0.0, 1.0);

	CGL_Vector3D::CGL_Vector3D(
										double _X,
										double _Y,
										double _Z,
										double _W
										)
	{
		X = _X;
		Y = _Y;
		Z = _Z;
		W = _W;
	}

	CGL_Vector3D CGL_Vector3D::VectorAddition(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB)
	{
		return CGL_Vector3D(_VectorA.X + _VectorB.X, _VectorA.Y + _VectorB.Y, _VectorA.Z + _VectorB.Z, _VectorA.W + _VectorB.W);
	}


	CGL_Vector3D CGL_Vector3D::VectorSubtraction(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB)
	{
		return CGL_Vector3D(
			_VectorA.X - _VectorB.X,
			_VectorA.Y - _VectorB.Y,
			_VectorA.Z - _VectorB.Z,
			_VectorA.W - _VectorB.W
			);
	}

	double CGL_Vector3D::Dot(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB, bool normalize)
	{
		double dot;
		if (normalize)
		{
			double normA = 1.0 / CGL_Geometry::VectorLength3D(_VectorA.X, _VectorA.Y, _VectorA.Z);
			double normB = 1.0 / CGL_Geometry::VectorLength3D(_VectorB.X, _VectorB.Y, _VectorB.Z);
			dot =	( (_VectorA.X * normA) * (_VectorB.X * normB) ) +
					( (_VectorA.Y * normA) * (_VectorB.Y * normB) ) +
					( (_VectorA.Z * normA) * (_VectorB.Z * normB) );
		}
		else
		{
			dot =	(_VectorA.X * _VectorB.X) +
					(_VectorA.Y * _VectorB.Y) + 
					(_VectorA.Z * _VectorB.Z);
		}
		return dot;
	}

	CGL_Vector3D CGL_Vector3D::Cross(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB)
	{
		return CGL_Vector3D(
			_VectorA.Y * _VectorB.Z - _VectorB.Y * _VectorA.Z,
			_VectorA.Z * _VectorB.X - _VectorB.Z * _VectorA.X,
			_VectorA.X * _VectorB.Y - _VectorB.X * _VectorA.Y
			);
	}

	//CGL_Vector3D CGL_Vector3D::Clone()
	//{
	//	return CGL_Vector3D(X,Y,Z);
	//}

	void CGL_Vector3D::Add(const CGL_Vector3D &_Vector)
	{
		X += _Vector.X;
		Y += _Vector.Y;
		Z += _Vector.Z;
		W += _Vector.W;
	}

	void CGL_Vector3D::Subtract(const CGL_Vector3D &_Vector)
	{
			X -= _Vector.X;
			Y -= _Vector.Y;
			Z -= _Vector.Z;
			W -= _Vector.W;
	}

	CGL_Vector3D CGL_Math::CGL_Values::CGL_Vector3D::Clone()
	{
		return CGL_Vector3D(X,Y,Z,W);
	}



	/*CGL_Vector3D CGL_Vector3D::Subtract(CGL_Vector3D _Vector)
	{
		return CGL_Vector3D(X - _Vector.X, Y - _Vector.Y, Z - _Vector.Z, W - _Vector.W);
	}*/

	void CGL_Vector3D::ScaleBy(double _Scalar)
	{
		X *= _Scalar;
		Y *= _Scalar;
		Z *= _Scalar;
		W *= _Scalar;
	}

	//double CGL_Vector3D::Dot(const CGL_Vector3D &_Vector)
	//{
	//	return ( (X*_Vector.X) + (Y*_Vector.Y) + (Z*_Vector.Z) );
	//}

	/*CGL_Vector3D CGL_Vector3D::Cross(const CGL_Vector3D &_Vector)
	{
		return CGL_Vector3D(
							Y * _Vector.Z - _Vector.Y * Z,
							Z * _Vector.X - _Vector.Z * X,
							X * _Vector.Y - _Vector.X * Y
							);
	}*/

	double CGL_Vector3D::Normalize()
	{
		double length = CGL_Geometry::VectorLength3D(X, Y, Z);
		double norm = 1.0 / length;
		if (norm != 0.0f)
		{
			X *= norm;
			Y *= norm;
			Z *= norm;
		}
		return length;
	}

	double CGL_Vector3D::GetLength() const
	{
		return sqrt(X*X + Y*Y + Z*Z);
	}

	std::string CGL_Vector3D::ToString()
	{
		std::ostringstream Convert;
		Convert << std::fixed;
		Convert << "CGL_Vector v0.1: ( " << std::setprecision(4) << X << " , " << Y << " , " << Z << " , " << W << " )";
		return Convert.str();
	}
