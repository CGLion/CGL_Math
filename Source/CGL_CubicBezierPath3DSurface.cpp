#include "CGL_CubicBezierPath3DSurface.h"
#include "CGL_Geometry.h"

namespace CGL_Math
{
	namespace CGL_Surfaces
	{
		void CGL_CubicBezierPath3DSurface::BuildSurface(bool _AutoCache, int _Precision)
		{
			//PathPoints = vector<CGL_Vector3D>();
			//PathPoints.reserve(Closed ? (Knots->size() * 3) : ((Knots->size() - 1) * 3 + 1));
			int NumPoints = (Closed ? (int(Knots->size()) * 3) : ((int(Knots->size()) - 1) * 3 + 1));

			for (int i = 0; i < NumPoints; i++)
			{
				switch (i % 3)
				{
				case 0:
				{
					PathPoints.push_back(Knots->at(int(i / 3)).GetPosition());
					break;
				}
				case 1:
				{
					PathPoints.push_back(Knots->at(int(i / 3)).GetWorldSpaceForwardTangent());
					break;
				}
				case 2:
				{
					if ((i == NumPoints - 1) && Closed)
					{
						PathPoints.push_back(Knots->at(0).GetWorldSpaceBackwardTangent());
					}
					else
					{
						PathPoints.push_back(Knots->at(int(i / 3) + 1).GetWorldSpaceBackwardTangent());
					}
					break;
				}
				}
			}

			Path = new CGL_CubicBezierPath3D(&PathPoints, Closed, _Precision, _AutoCache);
		}

		CGL_Matrix3D* CGL_CubicBezierPath3DSurface::GetMatrixAt(double _L, int _MinimalPrecision) const
		{
			CGL_Ray Ray = Path->GetRayAtRelativeLength(_L, _MinimalPrecision);
			int CurveIndex = Path->GetCurveIndexAtLength(_L, _MinimalPrecision);
			CGL_Matrix3D* UpMatrix = CGL_Matrix3D::Interpolate(
																Knots->at(CurveIndex),
																Knots->at((CurveIndex == Path->GetNumCurves() - 1) && Closed ? 0 : CurveIndex + 1),
																Path->GetPercentOnCurve(_L, _MinimalPrecision)
																);

			//upMatrix.invert();

			CGL_Vector3D UpVector = UpMatrix->GetZAxis();
			//trace("internal", upVector);
			UpVector.Normalize();
			//upVector.scaleBy( -1);

			CGL_Matrix3D* NewMatrix = new CGL_Matrix3D();
			NewMatrix->SetPosition(Ray.Position);
			
			CGL_Vector3D LookAtTarget = Ray.Position.Clone();
			LookAtTarget.Add(Ray.Direction);

			NewMatrix->LookAt(LookAtTarget, UpVector, 0);

			delete UpMatrix;

			return NewMatrix;
		}


		CGL_CubicBezierPath3DSurface::CGL_CubicBezierPath3DSurface(
																vector<CGL_CubicBezierPath3DSurfaceKnot>* _Knots,
																double _Width,
																bool _Closed,
																bool _AutoCache,
																int _Precision
																)
		{
			AutoCache = _AutoCache;
			Precision = _Precision;
			if (_Width > 0)
			{
				Width = _Width;
			}
			else
			{
				Width = 0.1;
			}

			Built = false;
			Closed = _Closed;
			CachedU = false;
			if (_Knots != NULL)
			{
				Knots = _Knots;
				BuildSurface(_AutoCache, Precision);
				Built = true;
			}
		}


		CGL_CubicBezierPath3DSurface::~CGL_CubicBezierPath3DSurface()
		{
		}

		CGL_Matrix3D* CGL_CubicBezierPath3DSurface::GetMatrixOnSurface(double _U, double _V, double _W) const
		{
			CGL_Vector3D Point = CGL_Vector3D(0.0f, (-Width * 0.5) + _U * Width, _W, 0.0f);
			CGL_Matrix3D* Matrix = GetMatrixAt(_V, Precision);
			Point = Matrix->TransformVector(Point);
			Matrix->SetPosition(Point);
			return Matrix;
		}
		CGL_Vector3D CGL_CubicBezierPath3DSurface::GetPointOnSurface(double _U, double _V, double _W) const
		{
			CGL_Vector3D Point = CGL_Vector3D(0.0f, _W, (-Width * 0.5) + _U * Width, 0.0f);
			CGL_Matrix3D* Matrix = GetMatrixAt(_V, Precision);
			Point = Matrix->TransformVector(Point);
			delete Matrix;
			return Point;
		}

		double CGL_CubicBezierPath3DSurface::GetLength() const
		{
			return Path->GetArcLength(Precision);
		}
		double CGL_CubicBezierPath3DSurface::GetWidth() const
		{
			return Width;
		}
		int CGL_CubicBezierPath3DSurface::GetNumKnots() const
		{
			return int(Knots->size());
		}
	}
}