#pragma once

#include <string>

namespace CGL_Math
{
	namespace CGL_Values
	{
		class CGL_Vector3D
		{
		public:
			static const CGL_Vector3D WORLD_X;
			static const CGL_Vector3D WORLD_Y;
			static const CGL_Vector3D WORLD_Z;


			CGL_Vector3D(double _X = 0.0, double _Y = 0.0, double _Z = 0.0, double _W = 0.0);
			double X, Y, Z, W;

			// operates on 4 components
			static CGL_Vector3D VectorAddition(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB);
			
			// operates on 4 components
			static CGL_Vector3D VectorSubtraction(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB);

			// uses only x y z
			static double Dot(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB, bool normalize = true);
			
			// uses only x y z
			static CGL_Vector3D Cross(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB);

			//CGL_Vector3D Clone();
			
			void Add(const CGL_Vector3D & _Vector);
			void Subtract(const CGL_Vector3D & _Vector);

			CGL_Vector3D Clone();

			//CGL_Vector3D Subtract(CGL_Vector3D _Vector);

			void ScaleBy(double _Scalar);
			
			// Calculated with X Y Z components
			//double Dot(const CGL_Vector3D &_Vector);

			// Calculated with X Y Z components
			//CGL_Vector3D Cross(const CGL_Vector3D &_Vector);

			/**
			* sets the length (magnitude) of the vector to 1.0
			*/
			double Normalize();


			double GetLength() const;

			/**
			* returns a string representation of the Vector
			*/
			std::string ToString();
		};
	}
}