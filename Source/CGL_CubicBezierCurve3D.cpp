#include "CGL_CubicBezierCurve3D.h"
#include "CGL_CurveUtil.h"
#include "CGL_Geometry.h"
#include <iostream>

using namespace CGL_Math;
using namespace CGL_Math::CGL_Curves;


//CGL_Math::CGL_Curves::CGL_CubicBezierCurve3D::CGL_CubicBezierCurve3D()
//{
//	P0 = CGL_Vector3D();
//	P1 = CGL_Vector3D();
//	P2 = CGL_Vector3D();
//	P3 = CGL_Vector3D();
//	AutoCache = false;
//	CachePrecision = 2;
//}

double CGL_Math::CGL_Curves::CGL_CubicBezierCurve3D::GetVersion()
{
	return 0.001;
}

CGL_CubicBezierCurve3D::CGL_CubicBezierCurve3D(
												const CGL_Vector3D* _PointA,
												const CGL_Vector3D* _TangentA,
												const CGL_Vector3D* _TangentB,
												const CGL_Vector3D* _PointB,
												bool _AutoCache,
												int _CachePrecision
												)
{
	P0 = _PointA;
	P1 = _TangentA;
	P2 = _TangentB;
	P3 = _PointB;
	AutoCache = _AutoCache;
	CachePrecision = _CachePrecision;
	Cached = false;
}

CGL_Ray CGL_CubicBezierCurve3D::GetRayAt(double _T) const
{
	CGL_Vector3D TangetPointA = CGL_Geometry::Interpolate3D(
															CGL_Geometry::Interpolate3D(*P0, *P1, _T),
															CGL_Geometry::Interpolate3D(*P1, *P2, _T),
															_T
															);
	CGL_Vector3D TangetPointB = CGL_Geometry::Interpolate3D(
															CGL_Geometry::Interpolate3D(*P1, *P2, _T),
															CGL_Geometry::Interpolate3D(*P2, *P3, _T),
															_T
															);

	CGL_Vector3D Position = CGL_Geometry::Interpolate3D(TangetPointA, TangetPointB, _T);
	CGL_Vector3D Direction;
	
	if (_T != 1.0)
	{
		Direction = CGL_Vector3D::VectorSubtraction(TangetPointB,Position);
	}
	else
	{
		Direction = CGL_Vector3D::VectorSubtraction(TangetPointA, Position);
		Direction.ScaleBy(-1.0);
	}
	Direction.Normalize();
	
	return CGL_Ray(Position,Direction);
}

CGL_Ray CGL_CubicBezierCurve3D::GetRayAtRelativeLength(double _L, int _MinimalPrecision)
{

	if (!Cached || (CachePrecision < _MinimalPrecision))
	{
		ProcessCurve(_MinimalPrecision);
	}

	double RealLength = fmod( _L , 1.0 ) * ((*(Cache.end()-1)).Position.W );

	int CurrentSample = (int)((Cache.size() - 1)/2);
	int MinSample = 0;
	int MaxSample = (int)(Cache.size() - 1);


	while ( ( MaxSample - MinSample ) > 1 )
	{
		if (RealLength < Cache[CurrentSample].Position.W)
		{
			MaxSample = CurrentSample;
		}
		else
		{
			MinSample = CurrentSample;
		}
		CurrentSample = MinSample + (int)((MaxSample-MinSample)/2);
	}

	std::cout << "NumSamples:"<< (int)(Cache.size()) << ", MinSample:" << MinSample << ", MaxSample:" << MaxSample << endl;

	double RemainingLengthPercent = (RealLength - Cache[MinSample].Position.W) /
		(Cache[MaxSample].Position.W - Cache[MinSample].Position.W);
	
	CGL_Vector3D ReturnPos = CGL_Geometry::Interpolate3D(
		Cache[MinSample].Position,
		Cache[MaxSample].Position,
		RemainingLengthPercent
		);

	CGL_Vector3D ReturnDir  = CGL_Geometry::Interpolate3D(
		Cache[MinSample].Direction,
		Cache[MaxSample].Direction,
		RemainingLengthPercent
		);
	ReturnDir.Normalize();
	return ( CGL_Ray(ReturnPos, ReturnDir));
}

void CGL_CubicBezierCurve3D::SetPoints(
										const CGL_Vector3D* _PointA,
										const CGL_Vector3D* _TangentA,
										const CGL_Vector3D* _TangentB,
										const CGL_Vector3D* _PointB
										)
{
	P0 = _PointA;
	P1 = _TangentA;
	P2 = _TangentB;
	P3 = _PointB;

	if (AutoCache)
	{
		ProcessCache(CachePrecision);
	}
	else
	{
		Cached = false;
	}
}

void CGL_CubicBezierCurve3D::ProcessCache(int _Precision)
{
	ProcessCurve(_Precision);
	Cached = true;
	CachePrecision = _Precision;
}

double CGL_CubicBezierCurve3D::GetArcLength(int _MinimalPrecision) const
{
	
	if (!(Cached && (CachePrecision >= _MinimalPrecision)))
	{
		ProcessCurve(_MinimalPrecision);
		//int a = 0;
	}
	return Cache.back().Position.W;
}

double CGL_CubicBezierCurve3D::GetStartTangentLength() const
{
	return CGL_Geometry::Distance3D(P0->X, P0->Y, P0->Z, P1->X, P1->Y, P1->Z);
}

double CGL_CubicBezierCurve3D::GetEndTangentLength() const
{
	return CGL_Geometry::Distance3D(P2->X, P2->Y, P2->Z, P3->X, P3->Y, P3->Z);
}

void CGL_CubicBezierCurve3D::DeleteCache()
{
	Cache.clear();
	Cached = false;
}

int CGL_CubicBezierCurve3D::GetNumCachedSamples() const
{
	if (Cached)
	{
		return (int)(Cache.size());
	}
	else
	{
		return 0;
	}
}

CGL_Ray CGL_CubicBezierCurve3D::GetSampleAt(int _Index) const
{
	if (Cached )
	{
		return (Cache[_Index % GetNumCachedSamples()]);
	}
	else
	{
		return CGL_Ray(CGL_Vector3D(),CGL_Vector3D());
	}
}

void CGL_CubicBezierCurve3D::ProcessCurve(int _Percision) const
{
	int NumSamples = CGL_CurveUtil::NumSamples(_Percision) - 2;
	int i;
	Cache.clear();
	Cache.reserve(NumSamples + 2);
	Cache.push_back(GetRayAt(0.0f));

	for (i = 1; i <= NumSamples; i++)
	{
		Cache.push_back( GetRayAt( (double)i / (double)(NumSamples + 1)));
	}
	Cache.push_back(GetRayAt(1.0f));
	


	double SegmentLength;
	double ArcLength = 0.0;
	Cache[0].Position.W = 0.0;
	
	for (i = 1; i <= NumSamples; i++)
	{
		SegmentLength = CGL_Geometry::Distance3D(
			Cache[i - 1].Position.X, Cache[i - 1].Position.Y, Cache[i - 1].Position.Z,
			Cache[i].Position.X, Cache[i].Position.Y, Cache[i].Position.Z
			);
		ArcLength += SegmentLength;
		Cache[i].Position.W = ArcLength;
	}
	SegmentLength = CGL_Geometry::Distance3D(
		Cache[NumSamples].Position.X, Cache[NumSamples].Position.Y, Cache[NumSamples].Position.Z,
		Cache[NumSamples + 1].Position.X, Cache[NumSamples + 1].Position.Y, Cache[NumSamples + 1].Position.Z
		);
	ArcLength += SegmentLength;
	Cache[NumSamples + 1].Position.W = ArcLength;
	Cached = true;
}


CGL_Vector3D CGL_CubicBezierCurve3D::GetPointA() const
{
	return *P0;
}
CGL_Vector3D CGL_CubicBezierCurve3D::GetTangentA() const
{
	return *P1;
}
CGL_Vector3D CGL_CubicBezierCurve3D::GetTangentB() const
{
	return *P2;
}
CGL_Vector3D CGL_CubicBezierCurve3D::GetPointB() const
{
	return *P3;
}