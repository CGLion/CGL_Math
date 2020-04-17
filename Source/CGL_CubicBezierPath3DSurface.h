#pragma once

#include <vector>
#include "CGL_CubicBezierPath3D.h"
#include "CGL_CubicBezierPath3DSurfaceKnot.h"
#include "CGL_Vector3D.h"
#include "CGL_Matrix3D.h"

using namespace CGL_Curves;
using namespace CGL_Values;

namespace CGL_Math
{
	namespace CGL_Surfaces
	{
		/**
		* Blah blah blah blah
		*/
		class CGL_CubicBezierPath3DSurface
		{
		private:
			
			//vector<CGL_Vector3D> PathPoints;
			//
			bool AutoCache;
			int Precision;
			double Width;
			bool Closed;
			bool Built;
			bool CachedU;
			int NumCachedUSamples;

			vector<CGL_Matrix3D> CachedUmatrices;

			void BuildSurface(bool _AutoCache, int _Precision);
			

		public:
			vector<CGL_Vector3D> PathPoints;
			CGL_Matrix3D* GetMatrixAt(double _L, int _MinimalPrecision) const;
			CGL_CubicBezierPath3D* Path;

			vector<CGL_CubicBezierPath3DSurfaceKnot>* Knots;

			CGL_CubicBezierPath3DSurface(
										vector<CGL_CubicBezierPath3DSurfaceKnot>* _Knots,
										double _Width,
										bool _Closed = false,
										bool _AutoCache = false,
										int _Precision = 5
										);

			~CGL_CubicBezierPath3DSurface();

			CGL_Matrix3D* GetMatrixOnSurface(double _U, double _V, double _W = 0) const;
			//
			CGL_Vector3D GetPointOnSurface(double _U, double _V, double _W = 0) const;

			double GetLength() const;
			double GetWidth() const;
			int GetNumKnots() const;
		};
	}
}