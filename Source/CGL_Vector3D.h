#pragma once

#include <string>

namespace CGL_Math
{
	namespace CGL_Values
	{
		/**
		 * @brief The CGL_Vector3D class represents a 4 dimantionl vector object with common vector operations
		 * @detailed 
		*/
		class CGL_Vector3D
		{
		public:
			static const CGL_Vector3D WORLD_X;
			static const CGL_Vector3D WORLD_Y;
			static const CGL_Vector3D WORLD_Z;


			CGL_Vector3D(double _X = 0.0, double _Y = 0.0, double _Z = 0.0, double _W = 0.0);
			double X, Y, Z, W;

			/**
			 * @brief Creates a new CGL_Vector3D object which is the result of adding _VectorA and _VectorB
			 * This static method is different from Add(const CGL_Vector3D & _Vector) as it doesn't require instanciating a CGL_Vector3D object to call it and generates a new one.
			 * @param _VectorA CGL_Vector3D
			 * @param _VectorB CGL_Vector3D
			 * @return CGL_Vector3D
			*/
			static CGL_Vector3D VectorAddition(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB);
			
			// operates on 4 components
			static CGL_Vector3D VectorSubtraction(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB);

			// uses only x y z
			static double Dot(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB, bool normalize = true);
			
			// uses only x y z
			static CGL_Vector3D Cross(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB);

			//CGL_Vector3D Clone();
			
			/**
			 * @brief Adds the supplied CGL_Vector3D value to this CGL_Vector3D (modifies it).
			 * This method is different from the static VectorAddition(const CGL_Vector3D &_VectorA, const CGL_Vector3D &_VectorB) method,
			 * As it doesn't instanciate a new CGL_Vector3D object but modifies the existing one, through which the methos was called.
			 * @param _Vector CGL_Vector3D
			*/
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