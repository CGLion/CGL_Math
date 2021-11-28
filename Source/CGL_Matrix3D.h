#pragma once
#pragma once
//CGL_Matrix3D.h

#include "CGL_Vector3D.h"
#include "CGL_Ray.h"
#include <vector>
#include <string>

using namespace std;
using namespace CGL_Math::CGL_Values;

namespace CGL_Math
{
	namespace CGL_Values
	{
		enum MatrixLookAtAxis { X, Y, Z };

		/**
		 * @brief The CGL_Matrix3D class represents a 4X4 matrix
		*/
		class CGL_Matrix3D
		{
		public:
			CGL_Matrix3D();

			/**
			* initializes a CGL_Matrix3D using the CGL_Ray as position and look at data,
			* The _UpVector as orientation around look at axis,
			* and _LookAtAxis to define which is the "looking" matrix axis 0, 1, 1 being X, Y, Z
			*/
			CGL_Matrix3D(const CGL_Ray& _Ray, const  CGL_Vector3D& _UpVector, int _LookAtAxis);

			~CGL_Matrix3D();

			/**
			* Set the matrixe's raw numerical data using a vector<double> where every 4 components will be a row 
			*/
			void SetData(vector<double> _Data);

			CGL_Vector3D GetXAxis() const;
			CGL_Vector3D GetYAxis() const;
			CGL_Vector3D GetZAxis() const;
			CGL_Vector3D GetPosition() const;


			void SetXAxis(const CGL_Vector3D& _XAxis);
			void SetYAxis(const CGL_Vector3D& _YAxis);
			void SetZAxis(const CGL_Vector3D& _ZAxis);
			void SetPosition(const CGL_Vector3D& _Position);

			/**
			* Multiply the matrix with a scalar value
			*/
			void Scale(double _Scalar);

			/**
			* Returns the determinant value of the matrix
			*/
			double Determinant() const;

			/**
			* Inverts the Matrix
			*/
			bool Invert();

			/**
			* Returns the world coordinates of the vector relative to the matrix
			*/
			CGL_Vector3D TransformVector(const CGL_Vector3D& _Vector) const;

			/**
			* Returns the world coordinates of the vector relative to the matrix disregarding the matrix position
			*/
			CGL_Vector3D DeltaTransformVector(const CGL_Vector3D& _Vector) const;

			
			/**
			* Orients the matrix so its _LookAtAxis (0 = X, 1 = Y, 2 = Z) will be pointing at the _LookAtTarget  
			*/
			void LookAt(const CGL_Vector3D &_LookAtTarget, const CGL_Vector3D &_UpVector,int _LookAtAxis);


			CGL_Vector3D RotationToQuat() const;

			void RotationFromQuat(const CGL_Vector3D& _Quat);

			static CGL_Matrix3D* Interpolate(const CGL_Matrix3D& _BaseMatrix, const CGL_Matrix3D& _TargetMatrix, double _T);
			void InterpolateTo(const CGL_Matrix3D & _TargetMatrix, double _T);

			double GetData(int _Row, int _Column) const;


			/**
			* returns a string representation of the Matrix
			*/
			std::string ToString() const;

			

		private:
			vector<double> Data{	1.0,0.0,0.0,0.0,
									0.0,1.0,0.0,0.0,
									0.0,0.0,1.0,0.0,
									0.0,0.0,0.0,1.0		};


			/**
			* returns the 0 - 15 index corresponding to a 0 based col / row coordinates ( 0 - 3 )
			*/
			inline int M(int _Row, int _Column) const;

			static vector<double> GenerateLookAtData(	const CGL_Vector3D &_Position,
														const  CGL_Vector3D &_LookAtTarget,
														const  CGL_Vector3D &_UpVector,
														int _LookAtAxis = 0);
		};
	}
}


