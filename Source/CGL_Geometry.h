#pragma once
// CGL_Geometry.h

#include "CGL_Vector3D.h"
#include "CGL_Matrix3D.h"
#include <cmath>

using namespace CGL_Math::CGL_Values;

namespace CGL_Math
{
	/**
	 * @brief A collection of static geometry operations
	*/
	class CGL_Geometry
	{
		public:
			static double GetVersion();
			
			// 
			//static const double PI;

			/** Returns the angle in radians of supplied angle in degrees.
			*  @param DegreesInput angle in degrees
			*/
			static inline double DegToRad(double _DegreesInput)
			{
				return (_DegreesInput / 360.0 * (2 * 3.14159265358979323846264338327950288));
			}

			/** Returns the angle in degrees of supplied angle in radians.
			*  @param RadiansInput angle in radians
			*/
			static inline double RadToDeg(double _RadiansInput)
			{
				return (_RadiansInput / (2.0 * 3.14159265358979323846264338327950288) * 360.0);
			}

			/** Returns the length of supplied x,y vector:
			*  @param X the X component of the vector
			*  @param Y the Y component of the vector
			*/
			static inline double VectorLength2D(double _X, double _Y)
			{
				return (sqrt(pow(_X, 2.0) + pow(_Y, 2.0)));
			}

			/** Returns the length of supplied x,y,z vector:
			*  @param X the X component of the vector
			*  @param Y the Y component of the vector
			*  @param Z the Z component of the vector
			*/
			static inline double VectorLength3D(double _X, double _Y, double _Z)
			{
				return (sqrt(pow(_X, 2.0) + pow(_Y, 2.0) + pow(_Z, 2.0)));
			}

			/** Returns the Distance between supplied point Ax,Ay and supplied point Bx,By:
			*  @param AX the X component of the point A
			*  @param AY the Y component of the point A
			*  @param BX the X component of the point B
			*  @param BY the Y component of the point B
			*/
			static inline double Distance2D(double _AX, double _AY, double _BX, double _BY)
			{
				return (sqrt(pow(_BX - _AX, 2.0) + pow(_BY - _AY, 2.0)));
			}

			/** Returns the Distance between supplied point Ax,Ay,Az and supplied point Bx,By,Bz:
			*  @param AX the X component of the point A
			*  @param AY the Y component of the point A
			*  @param AZ the Z component of the point A
			*  @param BX the X component of the point B
			*  @param BY the Y component of the point B
			*  @param BZ the Z component of the point B
			*/
			static inline double Distance3D(double _AX, double _AY, double _AZ, double _BX, double _BY, double _BZ)
			{
				return (sqrt(pow(_BX - _AX, 2.0) + pow(_BY - _AY, 2.0) + pow(_BZ - _AZ, 2.0)));
			}

			/** Returns the linear combination of A and B using wA and wB as factors:
			*  @param WA the weight of component A
			*  @param A Component A
			*  @param WB the weight of component B
			*  @param B Component B
			*/
			static inline double Combine(double _WA, double _A, double _WB, double _B)
			{
				return((_WA * _A) + (_WB * _B));
			}

			/** Returns a new Vector3D interpolated between _VectorA and _VectorB.
			*  @param _VectorA The first 3D vector
			*  @param _VectorB The second 3D vector
			*  @param _Percent number from 0.0 to 1.0
			*/
			static inline CGL_Vector3D Interpolate3D(const CGL_Vector3D& _VectorA, const CGL_Vector3D& _VectorB, double _Percent)
			{
				return (CGL_Vector3D(
					Combine(1.0 - _Percent, _VectorA.X, _Percent, _VectorB.X),
					Combine(1.0 - _Percent, _VectorA.Y, _Percent, _VectorB.Y),
					Combine(1.0 - _Percent, _VectorA.Z, _Percent, _VectorB.Z)
					));
			}

			/** Returns a new Vector3D that points from _VectorB to _VectorA.
			*  @param _VectorA The first 3D vector
			*  @param _VectorB The second 3D vector
			*/
			static inline CGL_Vector3D VectorSubtract(CGL_Vector3D &_VectorA, CGL_Vector3D &_VectorB)
			{
				return (CGL_Vector3D(
					_VectorA.X - _VectorB.X,
					_VectorA.Y - _VectorB.Y,
					_VectorA.Z - _VectorB.Z,
					_VectorA.W - _VectorB.W
					));
			}

			/** Returns the angle between supplied _X,_Y vector and the vector 1.0,0.0 in radians:
			*  @param _X
			*  @param _Y
			*/
			static inline double VectorAngle(double _X, double _Y)
			{
				return(_Y >= 0.0 ? (acos(_X / CGL_Geometry::VectorLength2D(_X, _Y))) : (-acos(_X / CGL_Geometry::VectorLength2D(_X, _Y))));
			}
			
			/** Returns the angle between supplied Ax,Ay vector and the supplied Bx,By vector in radians:
			*  @param AX the X component of the vector A
			*  @param AY the Y component of the vector A
			*  @param BX the X component of the vector B
			*  @param BY the Y component of the vector B
			*/
			static inline double VectorVectorAngle(double _AX, double _AY, double _BX, double _BY)
			{
				return (
					acos((_AX / CGL_Geometry::VectorLength2D(_AX, _AY)) *
						(_BX / CGL_Geometry::VectorLength2D(_BX, _BY)) +
						(_AY / CGL_Geometry::VectorLength2D(_AX, _AY)) *
						(_BY / CGL_Geometry::VectorLength2D(_BX, _BY)))
					);
			}

			// Returns the X coordinate for the supplied polar coordinate point (in Radians!!):
			static inline double PolarX(double _AngleRadians, double _Length = 1.0)
			{
				return(cos(_AngleRadians) * _Length);
			}

			// Returns the Y coordinate for the supplied polar coordinate point (in Radians!!):
			static inline double PolarY(double _AngleRadians, double _Length = 1.0)
			{
				return(sin(_AngleRadians) * _Length);
			}

			// Returns the linear interpolation of A and B at T:
			static inline double Interpolate(double _A, double _B, double _T)
			{
				return (((1.0 - _T) * _A) + (_T * _B));
			}

			// Returns the 0.0 > 1.0 value Modified by sine function 'easing':
			static inline double SineEase(double _Val)
			{
				return((sin((_Val * 3.14159265358979323846264338327950288) - (3.14159265358979323846264338327950288 / 2.0)) + 1.0) / 2.0);
			}

			// Returns the 0.0 > 1.0 value Modified by Bezier curve 'easing': 
			/*static double BezierEase(
				double _Val,
				double _StartTangentX = 0.333,
				double _EndTangentX = 0.666
				);*/

			// Returns the constant needed for aproximating a circle using Bezier curves:
			static inline double KAPPA()
			{
				return  (4.0 * ((sqrt(2.0) - 1.0) / 3.0));
			}


			// Returns the coordinates of _Point in _Matrix space
			static CGL_Vector3D GetPointInSpace( CGL_Vector3D _Point, CGL_Matrix3D _Matrix );

			// Returns the coordinates of a list of points in _Matrix space:
			static vector<CGL_Vector3D> GetPointsInspace(vector<CGL_Vector3D> _PointList, CGL_Matrix3D _Matrix);
			
			// Returns the world transform of a child matrix:
			static CGL_Matrix3D GetWorldTransform(CGL_Matrix3D &_ChildTransform, CGL_Matrix3D &_ParentTransform);


			//static CGL_Vector3D MatrixRotationToQuat(const CGL_Matrix3D& _Matrix);

			//static void MatrixRotationFromQuat(CGL_Matrix3D& _Matrix, const CGL_Vector3D& _Quat);

			static CGL_Vector3D Slerp(CGL_Vector3D _QuatA, CGL_Vector3D _QuatB, double _T);

			

		/*private:
			static double const PI;*/
	};
}
