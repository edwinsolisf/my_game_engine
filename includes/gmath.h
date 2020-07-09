#pragma once

#ifndef G_MATH
#define G_MATH

#include "Vector.h"
#include "Matrix.h"

namespace gmath
{

	extern const float PI_f;
	extern const double PI;
	
	extern const float E_f;
	extern const double E;

	float DegToRadf(const float& angle);
	float RadToDegf(const float& angle);

	double DegToRad(const double& angle);
	double DegToRad(const double& angle);

	template <unsigned int n>
	float GetVectorAngle(const Vector<n>& vec1, const Vector<n>& vec2) { return acosf(vec1.Direction().DotProduct(vec2.Direction())); }

	extern const Vector<3> posX;
	extern const Vector<3> negX;
	extern const Vector<3> posY;
	extern const Vector<3> negY;
	extern const Vector<3> posZ;
	extern const Vector<3> negZ;

	template <unsigned int n>
	Vector<n> normalize(const Vector<n>& vec) { return vec.Direction(); }
	template <unsigned int n>
	Vector<n> dot(const Vector<n>& vec1, const Vector<n>& vec2) { return vec1.DotProduct(vec2); }
	Vector<3> cross(const Vector<3>& v1, const Vector<3> v2);

	extern const Matrix<4, 4> identity;
	extern const Matrix<4, 4> reverse_identity; 
	
	Matrix<4, 4> scale(const float& scaling);
	Matrix<4, 4> translate(const Vector<3>& motion);
	Matrix<4, 4> rotateX(const float& angleInRads);
	Matrix<4, 4> rotateY(const float& angleInRads);
	Matrix<4, 4> rotateZ(const float& angleInRads);
	Matrix<4, 4> rotate(const float& angleInRads, const Vector<3>& axis);
	Matrix<4, 4> ortho(const float& left, const float&  right,
					   const float&  top, const float& bottom,
					   const float& near, const float&    far);

	Matrix<4, 4> perspective(const float& FOV, const float& aspectRatio, const float& zNear, const float& zFar);
}
#endif