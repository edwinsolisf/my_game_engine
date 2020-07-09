#include "gmath.h"

namespace gmath
{
	const float PI_f = 3.14159265358979323846f;
	const double PI = 3.141592653589793238462643383279502884;

	const float E_f = 2.71828182845904523536f;
	const double E = 2.71828182845904523536028747135266249;

	float DegToRadf(const float & angle)
	{
		return { angle * PI_f / 180.0f };
	}

	float RadToDegf(const float & angle)
	{
		return angle * 180.0f / PI_f;
	}

	double DegToRad(const double & angle)
	{
		return angle * PI / 180.0;
	}

	double RadToDeg(const double & angle)
	{
		return angle * 180.0 / PI;
	}

	const Vector<3> posX = {  1.0f, 0.0f, 0.0f };
	const Vector<3> negX = { -1.0f, 0.0f, 0.0f };
	const Vector<3> posY = {  0.0f, 1.0f, 0.0f };
	const Vector<3> negY = {  1.0f,-1.0f, 0.0f };
	const Vector<3> posZ = {  1.0f, 0.0f, 1.0f };
	const Vector<3> negZ = {  1.0f, 0.0f,-1.0f };

	Vector<3> cross(const Vector<3>& v1, const Vector<3> v2)
	{
		return v1.CrossProduct(v2);
	}

	Matrix<4, 4> scale(const float & scaling)
	{
		float a[16] =
		{
			scaling,    0.0f,    0.0f, 0.0f,
			   0.0f, scaling,    0.0f, 0.0f,
			   0.0f,    0.0f, scaling, 0.0f,
			   0.0f,    0.0f,    0.0f, 1.0f
		};

		return { a };
	}

	Matrix<4, 4> translate(const Vector<3>& vec)
	{
		float a[16] =
		{
			1.0f, 0.0f, 0.0f, vec.x,
			0.0f, 1.0f, 0.0f, vec.y,
			0.0f, 0.0f, 1.0f, vec.z,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		return { a };
	}

	Matrix<4, 4> rotateX(const float & angleInRads)
	{
		float a[16] =
		{
			1.0f,              0.0f,              0.0f, 0.0f,
			0.0f, cosf(angleInRads), -sinf(angleInRads), 0.0f,
			0.0f, sinf(angleInRads), cosf(angleInRads), 0.0f,
			0.0f,              0.0f,              0.0f, 1.0f
		};
		return { a };
	}

	Matrix<4, 4> rotateY(const float & angleInRads)
	{
		float a[16] =
		{
			 cosf(angleInRads), 0.0f, sinf(angleInRads), 0.0f,
						  0.0f, 1.0f,              0.0f, 0.0f,
			-sinf(angleInRads), 0.0f, cosf(angleInRads), 0.0f,
						  0.0f, 0.0f,              0.0f, 1.0f
		};
		return { a };
	}

	Matrix<4, 4> rotateZ(const float & angleInRads)
	{
		float a[16] =
		{
			cosf(angleInRads), -sinf(angleInRads), 0.0f, 0.0f,
			sinf(angleInRads),  cosf(angleInRads), 0.0f, 0.0f,
			             0.0f,               0.0f, 1.0f, 0.0f,
			             0.0f,               0.0f, 0.0f, 1.0f
		};
		return { a };
	}

	Matrix<4, 4> rotate(const float & angleInRads, const Vector<3>& axis)
	{
		const Vector<3>& temp = axis.Direction();
		float a[16] =
		{
			cosf(angleInRads) + (temp.x*temp.x)*(1 - cosf(angleInRads)),
			(temp.x*temp.y*(1 - cosf(angleInRads))) - (temp.z*sinf(angleInRads)),
			(temp.x*temp.z*(1 - cosf(angleInRads))) + (temp.y*sinf(angleInRads)),
			0.0f,
			(temp.y*temp.x*(1 - cosf(angleInRads))) + (temp.z*sinf(angleInRads)),
			cosf(angleInRads) + (temp.y*temp.y*(1 - cosf(angleInRads))),
			(temp.y*temp.z*(1 - cosf(angleInRads))) - (temp.x*sinf(angleInRads)),
			0.0f,
			(temp.z*temp.x*(1 - cosf(angleInRads))) - (temp.y*sinf(angleInRads)),
			(temp.z*temp.y*(1 - cosf(angleInRads))) + (temp.x*sinf(angleInRads)),
			cosf(angleInRads) + (temp.z*temp.z*(1 - cosf(angleInRads))),
			0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		return { a };
	}

	Matrix<4, 4> ortho(const float & left, const float & right, const float & top, const float & bottom, const float & far, const float & near)
	{
		float a[16] =
		{
			2.0f / (right - left),                 0.0f,               0.0f, -(right + left) / (right - left),
			                 0.0f, 2.0 / (top - bottom),               0.0f, -(top + bottom) / (top - bottom),
			                 0.0f,                 0.0f, 2.0 / (far - near),     -(far + near) / (far - near),
							 0.0f,                 0.0f,               0.0f,                             1.0f
		};
		return { a };
	}

	Matrix<4, 4> perspective(const float& FOVRads, const float& aspectRatio, const float& zNear, const float& zFar)
	{
		float a[16] =
		{
			1.0f/(aspectRatio*tanf(FOVRads/2.0f)),                 0.0f,                0.0f,                         0.0f,
							          0.0f, 1.0f / tanf(FOVRads / 2.0f),                0.0f,                         0.0f,
							          0.0f,                        0.0f, zFar/(zFar - zNear),     -zFar*zNear/(zFar-zNear),
							          0.0f,                        0.0f,                 1.0f,                         0.0f
		};

		return { a };
	}

}