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

	double CGL_Vector3D::Dot(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB)
	{
		return ((_VectorA.X*_VectorB.X) + (_VectorA.Y*_VectorB.Y) + (_VectorA.Z*_VectorB.Z));
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
		double Length = CGL_Geometry::VectorLength3D(X, Y, Z);
		if (Length != 0.0f)
		{
			X /= Length;
			Y /= Length;
			Z /= Length;
		}
		return Length;
	}

	double CGL_Vector3D::GetLength() const
	{
		return (sqrt(pow(X, 2.0) + pow(Y, 2.0) + pow(Z, 2.0)));
	}

	std::string CGL_Vector3D::ToString()
	{
		std::ostringstream Convert;
		Convert << std::fixed;
		Convert << "CGL_Vector v0.1: ( " << std::setprecision(4) << X << " , " << Y << " , " << Z << " , " << W << " )";
		return Convert.str();
	}
