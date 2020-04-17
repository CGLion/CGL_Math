
#include "CGL_Geometry.h"
#include "CGL_Vector3D.h"
#include "CGL_CubicBezierCurve3D.h"
#include <cmath>

//using namespace std;

namespace CGL_Math
{
	static const double PI = 3.14159265358979323846264338327950288;

	double CGL_Geometry::GetVersion()
	{
		return 0.003;
	}


	/*inline double CGL_Geometry::DegToRad(double _DegreesInput)
	{
		return (_DegreesInput / 360.0 * (2 * 3.14159265358979323846264338327950288));
	}*/

	/*inline double CGL_Geometry::RadToDeg(double _RadiansInput)
	{
		return (_RadiansInput / (2.0 * 3.14159265358979323846264338327950288) * 360.0);
	}*/

	/*inline double CGL_Geometry::VectorLength2D(double _X, double _Y)
	{
		return (sqrt(pow(_X, 2.0) + pow(_Y, 2.0)));
	}*/

	/*inline double CGL_Geometry::VectorLength3D(double _X, double _Y, double _Z)
	{
		return (sqrt(pow(_X, 2.0) + pow(_Y, 2.0) + pow(_Z, 2.0)));
	}*/

	/*inline double CGL_Geometry::Distance2D(double _AX, double _AY, double _BX, double _BY)
	{
		return (sqrt(pow(_BX - _AX, 2.0) + pow(_BY - _AY, 2.0)));
	}*/

	/*inline double CGL_Geometry::Distance3D(double _AX, double _AY, double _AZ, double _BX, double _BY, double _BZ)
	{
		return (sqrt(pow(_BX - _AX, 2.0) + pow(_BY - _AY, 2.0) + pow(_BZ - _AZ, 2.0)));
	}*/

	/*inline double CGL_Geometry::Combine(double _WA, double _A, double _WB, double _B)
	{
		return((_WA * _A) + (_WB * _B));
	}*/

	/*inline CGL_Vector3D CGL_Geometry::Interpolate3D(
											const CGL_Vector3D& _VectorA,
											const CGL_Vector3D& _VectorB,
											double _Percent
											)
	{
		return (CGL_Vector3D(
			Combine(1.0 - _Percent, _VectorA.X, _Percent, _VectorB.X),
			Combine(1.0 - _Percent, _VectorA.Y, _Percent, _VectorB.Y),
			Combine(1.0 - _Percent, _VectorA.Z, _Percent, _VectorB.Z),
			Combine(1.0 - _Percent, _VectorA.W, _Percent, _VectorB.W)
			));
	}*/

	/*inline CGL_Vector3D CGL_Geometry::VectorSubtract(
		CGL_Vector3D &_VectorA,
		CGL_Vector3D &_VectorB
		)
	{
		return (CGL_Vector3D(
			_VectorA.X - _VectorB.X,
			_VectorA.Y - _VectorB.Y,
			_VectorA.Z - _VectorB.Z,
			_VectorA.W - _VectorB.W
			));
	}*/

	/*inline double CGL_Geometry::VectorAngle(double _X, double _Y)
	{
		return( _Y >= 0.0 ? (acos(_X / CGL_Geometry::VectorLength2D(_X, _Y))) : (-acos(_X / CGL_Geometry::VectorLength2D(_X, _Y))));
	}*/

	/*inline double CGL_Geometry::VectorVectorAngle(double _AX, double _AY, double _BX, double _BY)
	{
		return (
				acos((_AX / CGL_Geometry::VectorLength2D(_AX, _AY)) *
					(_BX / CGL_Geometry::VectorLength2D(_BX, _BY)) +
					(_AY / CGL_Geometry::VectorLength2D(_AX, _AY)) *
					(_BY / CGL_Geometry::VectorLength2D(_BX, _BY)))
				);
	}*/

	/*inline double CGL_Geometry::PolarX(double _AngleRadians, double _Length)
	{
		return(cos(_AngleRadians) * _Length);
	}*/

	/*inline double CGL_Geometry::PolarY(double _AngleRadians, double _Length)
	{
		return(sin(_AngleRadians) * _Length);
	}*/

	/*inline double CGL_Geometry::Interpolate(double _A, double _B, double _T)
	{
		return (((1.0 - _T) * _A) + (_T * _B));
	}*/

	/*inline double CGL_Geometry::SineEase(double _Val)
	{
		return((sin((_Val * 3.14159265358979323846264338327950288) - (3.14159265358979323846264338327950288 / 2.0)) + 1.0) / 2.0);
	}*/

	//double CGL_Geometry::BezierEase(double _Val, double _StartTangentX, double _EndTangentX)
	//{
	//	CGL_Curves::CGL_CubicBezierCurve3D Curve = CGL_Curves::CGL_CubicBezierCurve3D(
	//															new CGL_Vector3D(0.0, 0.0, 0.0),
	//															new CGL_Vector3D(_StartTangentX, 0.0, 0.0),
	//															new CGL_Vector3D(_EndTangentX, 0.0, 0.0),
	//															new CGL_Vector3D(1.0, 1.0, 0.0)
	//															);
	//	return(Curve.GetRayAtRelativeLength(_Val, 6).Position.Y);
	//}

	/*inline double CGL_Geometry::KAPPA()
	{
		return  (4.0 * ((sqrt(2.0) - 1.0) / 3.0));
	}*/



	CGL_Vector3D CGL_Geometry::GetPointInSpace(CGL_Vector3D _Point, CGL_Matrix3D _Matrix)
	{
		bool Invert = _Matrix.Invert();
		CGL_Vector3D NewVector;
		if (Invert)
		{
			NewVector = _Matrix.TransformVector(_Point);
		}
		else
		{
			NewVector = CGL_Vector3D();
		}
		return NewVector;
	}

	vector<CGL_Vector3D> CGL_Geometry::GetPointsInspace(vector<CGL_Vector3D> _PointList, CGL_Matrix3D _Matrix)
	{
		bool Invert = _Matrix.Invert();
		vector<CGL_Vector3D> NewPointList = vector<CGL_Vector3D>();
		if (Invert)
		{
			for (unsigned int i = 0; i < _PointList.size(); i++)
			{
				NewPointList.push_back(_Matrix.TransformVector(_PointList[i]));
			}
		}
		return NewPointList;
	}

	CGL_Matrix3D CGL_Geometry::GetWorldTransform(CGL_Matrix3D &_ChildTransform, CGL_Matrix3D &_ParentTransform)
	{
		CGL_Matrix3D WorldTransform = CGL_Matrix3D();
		
		WorldTransform.SetXAxis(_ParentTransform.DeltaTransformVector(_ChildTransform.GetXAxis()));
		WorldTransform.SetYAxis(_ParentTransform.DeltaTransformVector(_ChildTransform.GetYAxis()));
		WorldTransform.SetZAxis(_ParentTransform.DeltaTransformVector(_ChildTransform.GetZAxis()));
		WorldTransform.SetPosition(_ParentTransform.DeltaTransformVector(_ChildTransform.GetPosition()));

		return WorldTransform;
	}

	//CGL_Vector3D CGL_Geometry::MatrixRotationToQuat(const CGL_Matrix3D & _Matrix){}

	//void CGL_Geometry::MatrixRotationFromQuat(CGL_Matrix3D & _Matrix, const CGL_Vector3D & _Quat){}

	CGL_Vector3D CGL_Geometry::Slerp(CGL_Vector3D _QuatA, CGL_Vector3D _QuatB, double _T)
	{
		// quaternion to return
		CGL_Vector3D _QuatT = CGL_Vector3D();
		// Calculate angle between them.
		double cosHalfTheta = (_QuatA.W * _QuatB.W) + (_QuatA.X * _QuatB.X) + (_QuatA.Y * _QuatB.Y) + (_QuatA.Z * _QuatB.Z);
		
		if (cosHalfTheta < 0.0f) {
			_QuatB.W = -_QuatB.W;
			_QuatB.X = -_QuatB.X;
			_QuatB.Y = -_QuatB.Y;
			_QuatB.Z = -_QuatB.Z;
			cosHalfTheta = -cosHalfTheta;
		}
		// if _QuatA=_QuatB or _QuatA=-_QuatB then theta = 0 and we can return _QuatA
		if (abs(cosHalfTheta) >= 1.0f)
		{
			_QuatT.W = _QuatA.W;
			_QuatT.X = _QuatA.X;
			_QuatT.Y = _QuatA.Y;
			_QuatT.Z = _QuatA.Z;
			return _QuatT;
		}
		// Calculate temporary values.
		double halfTheta = acos(cosHalfTheta);
		double sinHalfTheta = sqrt(1.0f - cosHalfTheta * cosHalfTheta);
		// if theta = 180 degrees then result is not fully defined
		// we could rotate around any axis normal to _QuatA or _QuatB
		if ( fabs(sinHalfTheta) < 0.001f) // fabs is floating point absolute
		{ 
			_QuatT.W = (_QuatA.W * 0.5 + _QuatB.W * 0.5);
			_QuatT.X = (_QuatA.X * 0.5 + _QuatB.X * 0.5);
			_QuatT.Y = (_QuatA.Y * 0.5 + _QuatB.Y * 0.5);
			_QuatT.Z = (_QuatA.Z * 0.5 + _QuatB.Z * 0.5);
			return _QuatT;
		}
		double ratioA = sin((1 - _T) * halfTheta) / sinHalfTheta;
		double ratioB = sin(_T * halfTheta) / sinHalfTheta;
		//calculate Quaternion.
		_QuatT.W = (_QuatA.W * ratioA + _QuatB.W * ratioB);
		_QuatT.X = (_QuatA.X * ratioA + _QuatB.X * ratioB);
		_QuatT.Y = (_QuatA.Y * ratioA + _QuatB.Y * ratioB);
		_QuatT.Z = (_QuatA.Z * ratioA + _QuatB.Z * ratioB);
		
		return _QuatT;
	}

}