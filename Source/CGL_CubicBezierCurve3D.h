#pragma once
// CGL_CubicBezierCurve3D.h

#include "CGL_Vector3D.h"
#include "CGL_Ray.h"
#include <vector>

using namespace CGL_Math;
using namespace CGL_Math::CGL_Values;
using namespace std;
namespace CGL_Math
{
	namespace CGL_Curves
	{
		class CGL_CubicBezierCurve3D
		{
		public:
			static double GetVersion();
			//
			//
			/**
			Creates a 3D Bezier Curve object using the suplied 3D points
			*/
			CGL_CubicBezierCurve3D(
									const CGL_Vector3D* _PointA,
									const CGL_Vector3D* _TangentA,
									const CGL_Vector3D* _TangentB,
									const CGL_Vector3D* _PointB,
									bool _AutoCache = false,
									int _CachePrecision = 5
									);

			/**
			Returns a CGL_Ray value of the position and tangent at time _T of the curve
			*/
			CGL_Ray GetRayAt( double _T ) const;

			/** Gets the position the 0 - 1 arc length on the curve.
			*  @param _l relative arc length on the curve from between 0 and 1;
			*  @param _minimal_percision the minimal precision the curve should
			* be approximated with for the length calculation.
			*/
			CGL_Ray GetRayAtRelativeLength(double _L, int _MinimalPrecision = 5);

			void SetPoints(
							const CGL_Vector3D* _PointA,
							const CGL_Vector3D* _TangentA,
							const CGL_Vector3D* _TangentB,
							const CGL_Vector3D* _PointB
							);

			void ProcessCache(int _Percision);

			double GetArcLength(int _MinimalPrecision = 5) const;

			double GetStartTangentLength() const;

			double GetEndTangentLength() const;

			void DeleteCache();

			int GetNumCachedSamples() const;

			// Curve must be cached and index must be valid
			CGL_Ray GetSampleAt(int _Index) const;

			CGL_Vector3D GetPointA() const;
			CGL_Vector3D GetTangentA() const;
			CGL_Vector3D GetTangentB() const;
			CGL_Vector3D GetPointB() const;

		private:
			const CGL_Vector3D* P0;
			const CGL_Vector3D* P1;
			const CGL_Vector3D* P2;
			const CGL_Vector3D* P3;

			bool AutoCache;
			mutable bool Cached;
			mutable vector<CGL_Ray> Cache;
			int CachePrecision;

			void ProcessCurve(int _Percision) const;
			
		};
	}
}