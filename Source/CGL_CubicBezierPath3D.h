#pragma once

#include <vector>
#include "CGL_CubicBezierCurve3D.h"
#include "CGL_Matrix3D.h"

using namespace std;
//
namespace CGL_Math
{
	namespace CGL_Curves
	{
		class CGL_CubicBezierPath3D
		{
		public:

			CGL_CubicBezierPath3D(
									const vector<CGL_Vector3D>* _Points,
									bool _Closed = false,
									int _Precision = 5,
									bool _AutoCache = false
									);

			~CGL_CubicBezierPath3D();

			/*static CGL_CubicBezierPath3D* BezierCircle(
				double _Radius,
				const CGL_Matrix3D& _Matrix,
				bool _AutoCache = false,
				int _Precision = 5
				);*/

			/**
			* Returns the arc length of the path
			* //
			*/
			double GetArcLength(int _MinimalPrecision = 5) const;

			/** Gets the position the 0 - 1 arc length on the curve.
			*  @param _l relative arc length on the curve from between 0 and 1;
			*  @param _minimal_percision the minimal precision the curve should
			* be approximated with for the length calculation.
			*/
			CGL_Ray GetRayAtRelativeLength(
				double _L,
				int _MinimalPrecision
				) const;

			void RebuildPath(int _Precision = 5, bool _AutoCache = false) const;

			int GetNumCachedSamples() const;

			int GetNumCurves() const;

			int GetCurveIndexAtLength(
										double _L,
										int _MinimalPercision,
										vector<CGL_CubicBezierCurve3D>* _Curves = NULL
										) const;

			CGL_CubicBezierCurve3D* GetCurveAtLength(double _L, int _MinimalPrecision) const;

			double GetPercentOnCurve(
									double _L,
									int _MinimalPrecision
									) const;

		private:
			const vector<CGL_Vector3D>* Points;
			bool DeletPointsOnDestruct;

			mutable vector<CGL_CubicBezierCurve3D> Curves;

			bool Closed;
			mutable bool Cached;
			bool AutoCache;
			mutable int CachePrecision;

			void BuildPath(int _Precision, bool _AutoCache) const;
		};
	}
}


