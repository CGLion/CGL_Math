#include "CGL_CubicBezierPath3D.h"
#include "CGL_CurveUtil.h"
#include "CGL_Geometry.h"
#include "CGL_Ray.h"
#include <cmath>

using namespace CGL_Values;

namespace CGL_Math
{
	namespace CGL_Curves
	{
		CGL_CubicBezierPath3D::CGL_CubicBezierPath3D(
														const vector<CGL_Vector3D>* _Points,
														bool _Closed,
														int _Precision,
														bool _AutoCache
														)
		{
			AutoCache = _AutoCache;
			CachePrecision = _Precision;
			Cached = false;
			Closed = _Closed;
			Points = _Points;
			
			Cached = AutoCache;
			BuildPath(CachePrecision, AutoCache);

			DeletPointsOnDestruct = false;
		}


		CGL_CubicBezierPath3D::~CGL_CubicBezierPath3D()
		{
			if (DeletPointsOnDestruct)
			{
				delete Points;
			}
		}

		/*CGL_CubicBezierPath3D* CGL_CubicBezierPath3D::BezierCircle(double _Radius, const CGL_Matrix3D& _Matrix, bool _AutoCache, int _Precision)
		{
			double kr = CGL_Geometry::KAPPA() * _Radius;
			vector<CGL_Vector3D>* CirclePoints = new vector<CGL_Vector3D>{
												CGL_Vector3D(0.0, 0.0, _Radius),
												CGL_Vector3D(kr, 0.0, _Radius),
												CGL_Vector3D(_Radius, 0.0, kr),
												CGL_Vector3D(_Radius, 0.0, 0.0),
												CGL_Vector3D(_Radius, 0.0, -kr),
												CGL_Vector3D(kr, 0.0, -_Radius),
												CGL_Vector3D(0.0, 0.0, -_Radius),
												CGL_Vector3D(-kr, 0.0, -_Radius),
												CGL_Vector3D(-_Radius, 0.0, -kr),
												CGL_Vector3D(-_Radius, 0.0, 0.0),
												CGL_Vector3D(-_Radius, 0.0, kr),
												CGL_Vector3D(-kr, 0.0, _Radius)
											};
			for (int i = 0; i < (int)(CirclePoints->size()); i++)
			{
				CirclePoints->at(i) = _Matrix.TransformVector(CirclePoints->at(i));
			}

			return(new CGL_CubicBezierPath3D(CirclePoints, _AutoCache, _Precision, true));
		}*/


		double CGL_CubicBezierPath3D::GetArcLength(int _MinimalPrecision) const
		{
			double ArcLength = 0.0;
			if (CachePrecision < _MinimalPrecision)
			{
				RebuildPath(_MinimalPrecision);
			}

			for (int i = 0; i < (int)(Curves.size()); i++)
			{
				ArcLength += Curves[i].GetArcLength(_MinimalPrecision);
			}

			return ArcLength;
		}


		/** Gets the position the 0 - 1 arc length on the curve.
		*  @param _l relative arc length on the curve from between 0 and 1;
		*  @param _minimal_percision the minimal precision the curve should
		* be approximated with for the length calculation.
		*/
		CGL_Ray CGL_CubicBezierPath3D::GetRayAtRelativeLength(
																double _L,
																int _MinimalPrecision
																) const
		{
			_L = fmod(_L,1.0);


			double RealLength = _L * GetArcLength(_MinimalPrecision);
			double MeasureLength = 0.0;
			int MeasureCurveIndex = 0;

			do
			{
				MeasureLength += Curves[MeasureCurveIndex].GetArcLength(_MinimalPrecision);
				MeasureCurveIndex++;
			} while (MeasureLength < RealLength);

			if (MeasureLength == RealLength)
			{
				return Curves[MeasureCurveIndex - 1].GetRayAt(1);
			}
			else
			{
				MeasureLength -= Curves[MeasureCurveIndex - 1].GetArcLength(_MinimalPrecision);
				double RemainingPercent = (RealLength - MeasureLength) / Curves[MeasureCurveIndex - 1].GetArcLength(_MinimalPrecision);
				return Curves[MeasureCurveIndex - 1].GetRayAtRelativeLength(RemainingPercent, _MinimalPrecision);
			}
			return CGL_Ray(CGL_Vector3D(),CGL_Vector3D());
		}


		void CGL_CubicBezierPath3D::RebuildPath(int _Precision, bool _AutoCache) const
		{
			BuildPath( _Precision, _AutoCache);
			if (_AutoCache)
			{
				Cached = true;
			}
		}

		int CGL_CubicBezierPath3D::GetNumCachedSamples() const
		{
			if (Cached)
			{
				return (((int)(Curves.size()) * (CGL_CurveUtil::NumSamples(CachePrecision) - 1)) + 1);
			}
			else
			{
				return 0;
			}
		}

		int CGL_CubicBezierPath3D::GetNumCurves() const
		{
			return (int)(Curves.size());
		}

		int CGL_CubicBezierPath3D::GetCurveIndexAtLength(
														double _L,
														int _MinimalPercision,
														vector<CGL_CubicBezierCurve3D>* _Curves
														) const
		{
			_L = fmod(_L, 1.0f);

			double RealLength = _L * GetArcLength(_MinimalPercision);
			double MeasureLength = 0.0f;
			int MeasureCurveIndex = 0;
			
			do
			{
				MeasureLength += Curves[MeasureCurveIndex].GetArcLength(_MinimalPercision);
				MeasureCurveIndex++;
			} while (MeasureLength < RealLength);

			return (MeasureCurveIndex - 1);
		}

		CGL_CubicBezierCurve3D* CGL_CubicBezierPath3D::GetCurveAtLength(double _L, int _MinimalPrecision) const
		{
			return &Curves[GetCurveIndexAtLength(_L, _MinimalPrecision)];
		}

		double CGL_CubicBezierPath3D::GetPercentOnCurve(double _L, int _MinimalPrecision) const
		{
			_L = fmod(_L,1.0f);


			double RealLength = _L * GetArcLength(_MinimalPrecision);
			double MeasureLength = 0.0f;
			int MeasureCurveIndex = 0;
			
			do
			{
				MeasureLength += Curves[MeasureCurveIndex].GetArcLength(_MinimalPrecision);
				MeasureCurveIndex++;
			} while (MeasureLength < RealLength);

			if (MeasureLength == RealLength)
			{
				return 1.0;
			}
			else
			{
				MeasureLength -= Curves[MeasureCurveIndex - 1].GetArcLength(_MinimalPrecision);
				return (RealLength - MeasureLength) / Curves[MeasureCurveIndex - 1].GetArcLength(_MinimalPrecision);
			}
		}


		void CGL_CubicBezierPath3D::BuildPath(int _Precision, bool _AutoCache) const
		{
			int NumCurves = Closed ? ((int)Points->size()) / 3 : (((int)Points->size())-1) / 3 ;
			
			Curves.clear();
			
			/*Curves.push_back(CGL_CubicBezierCurve3D(
				&(Points->at(0)),
				&(Points->at(1)),
				&(Points->at(2)),
				&(Points->at(3)),
				_AutoCache,
				_Precision
				));*/

			for (int i = 0; i < NumCurves; i++)
			{
				if (i < (NumCurves-1))
				{
					Curves.push_back(CGL_CubicBezierCurve3D(
															&(Points->at(i * 3 + 0)),
															&(Points->at(i * 3 + 1)),
															&(Points->at(i * 3 + 2)),
															&(Points->at(i * 3 + 3)),
															_AutoCache,
															_Precision
															));
					
					
				}
				else
				{
					Curves.push_back(CGL_CubicBezierCurve3D(
															&(Points->at(i * 3 + 0)),
															&(Points->at(i * 3 + 1)),
															&(Points->at(i * 3 + 2)),
															&(Points->at(Closed ? 0 : i * 3 + 3)),
															_AutoCache,
															_Precision
															));
				}
			}
		}
	}
}