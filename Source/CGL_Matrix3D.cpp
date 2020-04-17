#include "CGL_Matrix3D.h"
#include "CGL_Geometry.h"
#include <math.h>
#include <string>
#include <sstream>

using namespace CGL_Math::CGL_Values;

CGL_Matrix3D::CGL_Matrix3D()
{
}


CGL_Matrix3D::CGL_Matrix3D(const CGL_Ray &_Ray, const  CGL_Vector3D &_UpVector, int _LookAtAxis)
{
	Data = GenerateLookAtData(_Ray.Position, _Ray.Direction, _UpVector, _LookAtAxis);
}

CGL_Matrix3D::~CGL_Matrix3D()
{
}

CGL_Vector3D CGL_Matrix3D::GetXAxis() const
{
	return CGL_Vector3D(Data[M(0,0)], Data[M(1, 0)], Data[M(2, 0)], Data[M(3, 0)]);
}

CGL_Vector3D CGL_Matrix3D::GetYAxis() const
{
	return CGL_Vector3D(Data[M(0, 1)], Data[M(1, 1)], Data[M(2, 1)], Data[M(3, 1)]);
}

CGL_Vector3D CGL_Matrix3D::GetZAxis() const
{
	return CGL_Vector3D(Data[M(0, 2)], Data[M(1, 2)], Data[M(2, 2)], Data[M(3, 2)]);
}

CGL_Vector3D CGL_Matrix3D::GetPosition() const
{
	return CGL_Vector3D(Data[M(0, 3)], Data[M(1, 3)], Data[M(2, 3)], Data[M(3, 3)]);
}

void CGL_Matrix3D::SetXAxis(const CGL_Vector3D& _XAxis)
{
	Data[M(0, 0)] = _XAxis.X;
	Data[M(1, 0)] = _XAxis.Y;
	Data[M(2, 0)] = _XAxis.Z;
	Data[M(3, 0)] = _XAxis.W;
}

void CGL_Matrix3D::SetYAxis(const CGL_Vector3D& _YAxis)
{
	Data[M(0, 1)] = _YAxis.X;
	Data[M(1, 1)] = _YAxis.Y;
	Data[M(2, 1)] = _YAxis.Z;
	Data[M(3, 1)] = _YAxis.W;
}

void CGL_Matrix3D::SetZAxis(const CGL_Vector3D& _ZAxis)
{
	Data[M(0, 2)] = _ZAxis.X;
	Data[M(1, 2)] = _ZAxis.Y;
	Data[M(2, 2)] = _ZAxis.Z;
	Data[M(3, 2)] = _ZAxis.W;
}

void CGL_Matrix3D::SetPosition(const CGL_Vector3D& _Position)
{
	Data[M(0, 3)] = _Position.X;
	Data[M(1, 3)] = _Position.Y;
	Data[M(2, 3)] = _Position.Z;
	Data[M(3, 3)] = 1.0;
}

void CGL_Matrix3D::Scale(double _Scalar)
{
	for (int i = 0; i < 16; i++)
	{
		Data[i] *= _Scalar;
	}
}

double CGL_Matrix3D::Determinant() const
{
	double Det =  
		//m03*m12*m21*m30												- m02*m13*m21*m30												- m03*m11*m22*m30												+ m01*m13*m22*m30 +
		Data[M(0, 3)] * Data[M(1, 2)] * Data[M(2, 1)] * Data[M(3, 0)] - Data[M(0, 2)] * Data[M(1, 3)] * Data[M(2, 1)] * Data[M(3, 0)] - Data[M(0, 3)] * Data[M(1, 1)] * Data[M(2, 2)] * Data[M(3, 0)] + Data[M(0, 1)] * Data[M(1, 3)] * Data[M(2, 2)] * Data[M(3, 0)] +
		//m02*m11*m23*m30												- m01*m12*m23*m30												- m03*m12*m20*m31												+ m02*m13*m20*m31 +
		Data[M(0, 2)] * Data[M(1, 1)] * Data[M(2, 3)] * Data[M(3, 0)] - Data[M(0, 1)] * Data[M(1, 2)] * Data[M(2, 3)] * Data[M(3, 0)] - Data[M(0, 3)] * Data[M(1, 2)] * Data[M(2, 0)] * Data[M(3, 1)] + Data[M(0, 2)] * Data[M(1, 3)] * Data[M(2, 0)] * Data[M(3, 1)] +
		//m03*m10*m22*m31												- m00*m13*m22*m31												- m02*m10*m23*m31												+ m00*m12*m23*m31 +
		Data[M(0, 3)] * Data[M(1, 0)] * Data[M(2, 2)] * Data[M(3, 1)] - Data[M(0, 0)] * Data[M(1, 3)] * Data[M(2, 2)] * Data[M(3, 1)] - Data[M(0, 2)] * Data[M(1, 0)] * Data[M(2, 3)] * Data[M(3, 1)] + Data[M(0, 0)] * Data[M(1, 2)] * Data[M(2, 3)] * Data[M(3, 1)] +
		//m03*m11*m20*m32												- m01*m13*m20*m32												- m03*m10*m21*m32												+ m00*m13*m21*m32 +
		Data[M(0, 3)] * Data[M(1, 1)] * Data[M(2, 0)] * Data[M(3, 2)] - Data[M(0, 1)] * Data[M(1, 3)] * Data[M(2, 0)] * Data[M(3, 2)] - Data[M(0, 3)] * Data[M(1, 0)] * Data[M(2, 1)] * Data[M(3, 2)] + Data[M(0, 0)] * Data[M(1, 3)] * Data[M(2, 1)] * Data[M(3, 2)] +
		//m01*m10*m23*m32												- m00*m11*m23*m32												- m02*m11*m20*m33												+ m01*m12*m20*m33 +
		Data[M(0, 1)] * Data[M(1, 0)] * Data[M(2, 3)] * Data[M(3, 2)] - Data[M(0, 0)] * Data[M(1, 1)] * Data[M(2, 3)] * Data[M(3, 2)] - Data[M(0, 2)] * Data[M(1, 1)] * Data[M(2, 0)] * Data[M(3, 3)] + Data[M(0, 1)] * Data[M(1, 2)] * Data[M(2, 0)] * Data[M(3, 3)] +
		//m02*m10*m21*m33												- m00*m12*m21*m33												- m01*m10*m22*m33												+ m00*m11*m22*m33;
		Data[M(0, 2)] * Data[M(1, 0)] * Data[M(2, 1)] * Data[M(3, 3)] - Data[M(0, 0)] * Data[M(1, 2)] * Data[M(2, 1)] * Data[M(3, 3)] - Data[M(0, 1)] * Data[M(1, 0)] * Data[M(2, 2)] * Data[M(3, 3)] + Data[M(0, 0)] * Data[M(1, 1)] * Data[M(2, 2)] * Data[M(3, 3)];
	return Det;
}

bool CGL_Matrix3D::Invert()
{
	double Det = Determinant();
	if (Det != 0.0)
	{
		double M00 = Data[M(1, 2)] * Data[M(2, 3)] * Data[M(3, 1)] - Data[M(1, 3)] * Data[M(2, 2)] * Data[M(3, 1)] + Data[M(1, 3)] * Data[M(2, 1)] * Data[M(3, 2)] - Data[M(1, 1)] * Data[M(2, 3)] * Data[M(3, 2)] - Data[M(1, 2)] * Data[M(2, 1)] * Data[M(3, 3)] + Data[M(1, 1)] * Data[M(2, 2)] * Data[M(3, 3)];
		double M01 = Data[M(0, 3)] * Data[M(2, 2)] * Data[M(3, 1)] - Data[M(0, 2)] * Data[M(2, 3)] * Data[M(3, 1)] - Data[M(0, 3)] * Data[M(2, 1)] * Data[M(3, 2)] + Data[M(0, 1)] * Data[M(2, 3)] * Data[M(3, 2)] + Data[M(0, 2)] * Data[M(2, 1)] * Data[M(3, 3)] - Data[M(0, 1)] * Data[M(2, 2)] * Data[M(3, 3)];
		double M02 = Data[M(0, 2)] * Data[M(1, 3)] * Data[M(3, 1)] - Data[M(0, 3)] * Data[M(1, 2)] * Data[M(3, 1)] + Data[M(0, 3)] * Data[M(1, 1)] * Data[M(3, 2)] - Data[M(0, 1)] * Data[M(1, 3)] * Data[M(3, 2)] - Data[M(0, 2)] * Data[M(1, 1)] * Data[M(3, 3)] + Data[M(0, 1)] * Data[M(1, 2)] * Data[M(3, 3)];
		double M03 = Data[M(0, 3)] * Data[M(1, 2)] * Data[M(2, 1)] - Data[M(0, 2)] * Data[M(1, 3)] * Data[M(2, 1)] - Data[M(0, 3)] * Data[M(1, 1)] * Data[M(2, 2)] + Data[M(0, 1)] * Data[M(1, 3)] * Data[M(2, 2)] + Data[M(0, 2)] * Data[M(1, 1)] * Data[M(2, 3)] - Data[M(0, 1)] * Data[M(1, 2)] * Data[M(2, 3)];
		double M10 = Data[M(1, 3)] * Data[M(2, 2)] * Data[M(3, 0)] - Data[M(1, 2)] * Data[M(2, 3)] * Data[M(3, 0)] - Data[M(1, 3)] * Data[M(2, 0)] * Data[M(3, 2)] + Data[M(1, 0)] * Data[M(2, 3)] * Data[M(3, 2)] + Data[M(1, 2)] * Data[M(2, 0)] * Data[M(3, 3)] - Data[M(1, 0)] * Data[M(2, 2)] * Data[M(3, 3)];
		double M11 = Data[M(0, 2)] * Data[M(2, 3)] * Data[M(3, 0)] - Data[M(0, 3)] * Data[M(2, 2)] * Data[M(3, 0)] + Data[M(0, 3)] * Data[M(2, 0)] * Data[M(3, 2)] - Data[M(0, 0)] * Data[M(2, 3)] * Data[M(3, 2)] - Data[M(0, 2)] * Data[M(2, 0)] * Data[M(3, 3)] + Data[M(0, 0)] * Data[M(2, 2)] * Data[M(3, 3)];
		double M12 = Data[M(0, 3)] * Data[M(1, 2)] * Data[M(3, 0)] - Data[M(0, 2)] * Data[M(1, 3)] * Data[M(3, 0)] - Data[M(0, 3)] * Data[M(1, 0)] * Data[M(3, 2)] + Data[M(0, 0)] * Data[M(1, 3)] * Data[M(3, 2)] + Data[M(0, 2)] * Data[M(1, 0)] * Data[M(3, 3)] - Data[M(0, 0)] * Data[M(1, 2)] * Data[M(3, 3)];
		double M13 = Data[M(0, 2)] * Data[M(1, 3)] * Data[M(2, 0)] - Data[M(0, 3)] * Data[M(1, 2)] * Data[M(2, 0)] + Data[M(0, 3)] * Data[M(1, 0)] * Data[M(2, 2)] - Data[M(0, 0)] * Data[M(1, 3)] * Data[M(2, 2)] - Data[M(0, 2)] * Data[M(1, 0)] * Data[M(2, 3)] + Data[M(0, 0)] * Data[M(1, 2)] * Data[M(2, 3)];
		double M20 = Data[M(1, 1)] * Data[M(2, 3)] * Data[M(3, 0)] - Data[M(1, 3)] * Data[M(2, 1)] * Data[M(3, 0)] + Data[M(1, 3)] * Data[M(2, 0)] * Data[M(3, 1)] - Data[M(1, 0)] * Data[M(2, 3)] * Data[M(3, 1)] - Data[M(1, 1)] * Data[M(2, 0)] * Data[M(3, 3)] + Data[M(1, 0)] * Data[M(2, 1)] * Data[M(3, 3)];
		double M21 = Data[M(0, 3)] * Data[M(2, 1)] * Data[M(3, 0)] - Data[M(0, 1)] * Data[M(2, 3)] * Data[M(3, 0)] - Data[M(0, 3)] * Data[M(2, 0)] * Data[M(3, 1)] + Data[M(0, 0)] * Data[M(2, 3)] * Data[M(3, 1)] + Data[M(0, 1)] * Data[M(2, 0)] * Data[M(3, 3)] - Data[M(0, 0)] * Data[M(2, 1)] * Data[M(3, 3)];
		double M22 = Data[M(0, 1)] * Data[M(1, 3)] * Data[M(3, 0)] - Data[M(0, 3)] * Data[M(1, 1)] * Data[M(3, 0)] + Data[M(0, 3)] * Data[M(1, 0)] * Data[M(3, 1)] - Data[M(0, 0)] * Data[M(1, 3)] * Data[M(3, 1)] - Data[M(0, 1)] * Data[M(1, 0)] * Data[M(3, 3)] + Data[M(0, 0)] * Data[M(1, 1)] * Data[M(3, 3)];
		double M23 = Data[M(0, 3)] * Data[M(1, 1)] * Data[M(2, 0)] - Data[M(0, 1)] * Data[M(1, 3)] * Data[M(2, 0)] - Data[M(0, 3)] * Data[M(1, 0)] * Data[M(2, 1)] + Data[M(0, 0)] * Data[M(1, 3)] * Data[M(2, 1)] + Data[M(0, 1)] * Data[M(1, 0)] * Data[M(2, 3)] - Data[M(0, 0)] * Data[M(1, 1)] * Data[M(2, 3)];
		double M30 = Data[M(1, 2)] * Data[M(2, 1)] * Data[M(3, 0)] - Data[M(1, 1)] * Data[M(2, 2)] * Data[M(3, 0)] - Data[M(1, 2)] * Data[M(2, 0)] * Data[M(3, 1)] + Data[M(1, 0)] * Data[M(2, 2)] * Data[M(3, 1)] + Data[M(1, 1)] * Data[M(2, 0)] * Data[M(3, 2)] - Data[M(1, 0)] * Data[M(2, 1)] * Data[M(3, 2)];
		double M31 = Data[M(0, 1)] * Data[M(2, 2)] * Data[M(3, 0)] - Data[M(0, 2)] * Data[M(2, 1)] * Data[M(3, 0)] + Data[M(0, 2)] * Data[M(2, 0)] * Data[M(3, 1)] - Data[M(0, 0)] * Data[M(2, 2)] * Data[M(3, 1)] - Data[M(0, 1)] * Data[M(2, 0)] * Data[M(3, 2)] + Data[M(0, 0)] * Data[M(2, 1)] * Data[M(3, 2)];
		double M32 = Data[M(0, 2)] * Data[M(1, 1)] * Data[M(3, 0)] - Data[M(0, 1)] * Data[M(1, 2)] * Data[M(3, 0)] - Data[M(0, 2)] * Data[M(1, 0)] * Data[M(3, 1)] + Data[M(0, 0)] * Data[M(1, 2)] * Data[M(3, 1)] + Data[M(0, 1)] * Data[M(1, 0)] * Data[M(3, 2)] - Data[M(0, 0)] * Data[M(1, 1)] * Data[M(3, 2)];
		double M33 = Data[M(0, 1)] * Data[M(1, 2)] * Data[M(2, 0)] - Data[M(0, 2)] * Data[M(1, 1)] * Data[M(2, 0)] + Data[M(0, 2)] * Data[M(1, 0)] * Data[M(2, 1)] - Data[M(0, 0)] * Data[M(1, 2)] * Data[M(2, 1)] - Data[M(0, 1)] * Data[M(1, 0)] * Data[M(2, 2)] + Data[M(0, 0)] * Data[M(1, 1)] * Data[M(2, 2)];
		
		Data[M(0, 0)] = M00;
		Data[M(0, 1)] = M01;
		Data[M(0, 2)] = M02;
		Data[M(0, 3)] = M03;
		Data[M(1, 0)] = M10;
		Data[M(1, 1)] = M11;
		Data[M(1, 2)] = M12;
		Data[M(1, 3)] = M13;
		Data[M(2, 0)] = M20;
		Data[M(2, 1)] = M21;
		Data[M(2, 2)] = M22;
		Data[M(2, 3)] = M23;
		Data[M(3, 0)] = M30;
		Data[M(3, 1)] = M31;
		Data[M(3, 2)] = M32;
		Data[M(3, 3)] = M33;
		
		Scale(1 / Det);
		return true;
	}
	else
	{
		return false;
	}
}

CGL_Vector3D CGL_Matrix3D::TransformVector(const CGL_Vector3D& _Vector) const
{
	return CGL_Vector3D(
		( (_Vector.X * Data[M(0, 0)]) + (_Vector.Y * Data[M(0, 1)]) + (_Vector.Z * Data[M(0, 2)]) ) + Data[M(0, 3)],
		( (_Vector.X * Data[M(1, 0)]) + (_Vector.Y * Data[M(1, 1)]) + (_Vector.Z * Data[M(1, 2)]) ) + Data[M(1, 3)],
		( (_Vector.X * Data[M(2, 0)]) + (_Vector.Y * Data[M(2, 1)]) + (_Vector.Z * Data[M(2, 2)]) ) + Data[M(2, 3)]
		);
}

CGL_Vector3D CGL_Matrix3D::DeltaTransformVector(const CGL_Vector3D& _Vector) const
{
	return CGL_Vector3D(
		( (_Vector.X * Data[M(0, 0)]) + (_Vector.Y * Data[M(0, 1)]) + (_Vector.Z * Data[M(0, 2)]) ),
		( (_Vector.X * Data[M(1, 0)]) + (_Vector.Y * Data[M(1, 1)]) + (_Vector.Z * Data[M(1, 2)]) ),
		( (_Vector.X * Data[M(2, 0)]) + (_Vector.Y * Data[M(2, 1)]) + (_Vector.Z * Data[M(2, 2)]) )
		);
}

void CGL_Matrix3D::LookAt(const CGL_Vector3D & _LookAtTarget, const CGL_Vector3D & _UpVector, int _LookAtAxis)
{
	Data = GenerateLookAtData(GetPosition(), _LookAtTarget, _UpVector,_LookAtAxis);
}

CGL_Vector3D CGL_Matrix3D::RotationToQuat() const
{
	CGL_Vector3D Quat = CGL_Vector3D();

	double Tr = Data[M(0, 0)] + Data[M(1, 1)] + Data[M(2, 2)];//float tr = m00 + m11 + m22
	double S;
	if (Tr > 0.0f)//	if (tr > 0) {
	{
		S = sqrt(1.0 + Tr) * 2.0f;//	float S = sqrt(tr + 1.0) * 2; // S=4*qw 
		Quat.W = 0.25f * S;//qw = 0.25 * S;
		Quat.X = (Data[M(2, 1)] - Data[M(1, 2)]) / S;//	qx = (m21 - m12) / S;
		Quat.Y = (Data[M(0, 2)] - Data[M(2, 0)]) / S;//	qy = (m02 - m20) / S;
		Quat.Z = (Data[M(1, 0)] - Data[M(0, 1)]) / S;//	qz = (m10 - m01) / S;
	}
	else if ((Data[M(0, 0)] > Data[M(1, 1)]) && (Data[M(0, 0)] > Data[M(2, 2)]))//	else if ((m00 > m11)&(m00 > m22))
	{
		S = sqrt(1.0f + Data[M(0, 0)] - Data[M(1, 1)] - Data[M(2, 2)]) * 2.0;//	float S = sqrt(1.0 + m00 - m11 - m22) * 2; // S=4*qx 
		Quat.W = (Data[M(2, 1)] - Data[M(1, 2)]) / S;//	qw = (m21 - m12) / S;
		Quat.X = 0.25f * S;//qx = 0.25 * S;
		Quat.Y = (Data[M(0, 1)] + Data[M(1, 0)]) / S;//	qy = (m01 + m10) / S;
		Quat.Z = (Data[M(0, 2)] + Data[M(2, 0)]) / S;//	qz = (m02 + m20) / S;
	}
	else if (Data[M(1, 1)] > Data[M(2, 2)])//	else if (m11 > m22)
	{
		S = sqrt(1.0 + Data[M(1, 1)] - Data[M(0, 0)] - Data[M(2, 2)]) * 2.0f;//	float S = sqrt(1.0 + m11 - m00 - m22) * 2; // S=4*qy
		Quat.W = (Data[M(0, 2)] - Data[M(2, 0)]) / S;//		qw = (m02 - m20) / S;
		Quat.X = (Data[M(0, 1)] + Data[M(1, 0)]) / S;//		qx = (m01 + m10) / S;
		Quat.Y = 0.25f * S;//		qy = 0.25 * S;
		Quat.Z = (Data[M(1, 2)] + Data[M(2, 1)]) / S;//		qz = (m12 + m21) / S;
	}
	else
	{
		S = sqrt(1.0 + Data[M(2, 2)] - Data[M(0, 0)] - Data[M(1, 1)]) * 2.0f;//		float S = sqrt(1.0 + m22 - m00 - m11) * 2; // S=4*qz
		Quat.W = (Data[M(1, 0)] - Data[M(0, 1)]) / S;//		qw = (m10 - m01) / S;
		Quat.X = (Data[M(0, 2)] + Data[M(2, 0)]) / S;//		qx = (m02 + m20) / S;
		Quat.Y = (Data[M(1, 2)] + Data[M(2, 1)]) / S;//		qy = (m12 + m21) / S;
		Quat.Z = 0.25f * S;//		qz = 0.25 * S;
	}
	return Quat;
}

void CGL_Matrix3D::RotationFromQuat(const CGL_Vector3D& _Quat)
{
	double sqw = _Quat.W * _Quat.W;
	double sqx = _Quat.X * _Quat.X;
	double sqy = _Quat.Y * _Quat.Y;
	double sqz = _Quat.Z * _Quat.Z;

	// invs (inverse square length) is only required if quaternion is not already normalised
	double invs = 1.0f / (sqx + sqy + sqz + sqw);

	Data[M(0, 0)] = ( sqx - sqy - sqz + sqw) * invs; // since sqw + sqx + sqy + sqz =1/invs*invs
	Data[M(1, 1)] = (-sqx + sqy - sqz + sqw) * invs;
	Data[M(2, 2)] = (-sqx - sqy + sqz + sqw) * invs;

	double tmp1 = _Quat.X * _Quat.Y;
	double tmp2 = _Quat.Z * _Quat.W;
	Data[M(1, 0)] = 2.0f * (tmp1 + tmp2) * invs;
	Data[M(0, 1)] = 2.0f * (tmp1 - tmp2) * invs;

	tmp1 = _Quat.X * _Quat.Z;
	tmp2 = _Quat.Y * _Quat.W;
	Data[M(2, 0)] = 2.0 * (tmp1 - tmp2) * invs;
	Data[M(0, 2)] = 2.0 * (tmp1 + tmp2) * invs;

	tmp1 = _Quat.Y * _Quat.Z;
	tmp2 = _Quat.X * _Quat.W;
	Data[M(2, 1)] = 2.0 * (tmp1 + tmp2) * invs;
	Data[M(1, 2)] = 2.0 * (tmp1 - tmp2) * invs;
}

CGL_Matrix3D* CGL_Matrix3D::Interpolate(const CGL_Matrix3D & _BaseMatrix, const CGL_Matrix3D & _TargetMatrix, double _T)
{
	CGL_Matrix3D* NewMatrix = new CGL_Matrix3D();
	NewMatrix->RotationFromQuat(CGL_Geometry::Slerp(_BaseMatrix.RotationToQuat(), _TargetMatrix.RotationToQuat(), _T));
	NewMatrix->SetPosition(CGL_Geometry::Interpolate3D(_BaseMatrix.GetPosition(), _TargetMatrix.GetPosition(), _T));
	return NewMatrix;
}

void CGL_Matrix3D::InterpolateTo(const CGL_Matrix3D & _TargetMatrix, double _T)
{
	RotationFromQuat(CGL_Geometry::Slerp(RotationToQuat(), _TargetMatrix.RotationToQuat(),_T));
	SetPosition(CGL_Geometry::Interpolate3D(GetPosition(),_TargetMatrix.GetPosition(), _T));
}

double CGL_Matrix3D::GetData(int _Row, int _Column) const
{
	return Data[M(_Row,_Column)];
}

void CGL_Matrix3D::SetData(vector<double> _Data)
{
	Data = _Data;
}

std::string CGL_Matrix3D::ToString() const
{
	std::ostringstream Convert;
	Convert << "CGL_Matrix3D v0.1:( " << GetXAxis().ToString() << " , " << GetYAxis().ToString() << " , " << GetZAxis().ToString() << " , " << GetPosition().ToString() << " )";
	return Convert.str();
}

inline int CGL_Matrix3D::M( int _Row, int _Column ) const
{
	return ( ( 4 * (_Row) ) + _Column);
}

vector<double> CGL_Matrix3D::GenerateLookAtData(const CGL_Vector3D &_Position,
												const CGL_Vector3D &_LookAtTarget,
												const CGL_Vector3D &_UpVector,
												int _LookAtAxis)
{
	CGL_Vector3D RollAxis = CGL_Vector3D::VectorSubtraction(_LookAtTarget, _Position );
	RollAxis.Normalize();

	CGL_Vector3D PitchAxis = CGL_Vector3D::Cross(_UpVector, RollAxis );
	PitchAxis.Normalize();

	CGL_Vector3D YawAxis = CGL_Vector3D::Cross(RollAxis,PitchAxis);
	YawAxis.Normalize();

	RollAxis.W = -(CGL_Vector3D::Dot(RollAxis,_Position));
	PitchAxis.W = -(CGL_Vector3D::Dot(PitchAxis, _Position));
	YawAxis.W = -(CGL_Vector3D::Dot(YawAxis, _Position));

	vector<double> Data{	1.0,0.0,0.0,0.0,
							0.0,1.0,0.0,0.0,
							0.0,0.0,1.0,0.0,
							0.0,0.0,0.0,1.0		};
	
	Data[ 0 + _LookAtAxis] = RollAxis.X;
	Data[ 4 + _LookAtAxis] = RollAxis.Y;
	Data[ 8 + _LookAtAxis] = RollAxis.Z;
	Data[12 + _LookAtAxis] = RollAxis.W;

	Data[ 0 + ((_LookAtAxis + 1) % 3)] = PitchAxis.X;
	Data[ 4 + ((_LookAtAxis + 1) % 3)] = PitchAxis.Y;
	Data[ 8 + ((_LookAtAxis + 1) % 3)] = PitchAxis.Z;
	Data[12 + ((_LookAtAxis + 1) % 3)] = PitchAxis.W;

	Data[ 0 + ((_LookAtAxis + 2) % 3)] = YawAxis.X;
	Data[ 4 + ((_LookAtAxis + 2) % 3)] = YawAxis.Y;
	Data[ 8 + ((_LookAtAxis + 2) % 3)] = YawAxis.Z;
	Data[12 + ((_LookAtAxis + 2) % 3)] = YawAxis.W;

	Data[3] = _Position.X;
	Data[7] = _Position.Y;
	Data[11] = _Position.Z;
	Data[15] = 1.0; //_Position.W Blah;

	return Data;
}
