#include "Vector.h"

namespace gmath
{
	Vector<3>::Vector(const Vector<2>& other, const float& _z)
	{
		x = other.x;
		y = other.y;
		z = _z;
	}

	Vector<4>::Vector(const Vector<3>& other, const float& _w)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = _w;
	}

	Vector<2> Vector<3>::ToVec2() const
	{
		return { x,y };
	}

	Vector<3> Vector<4>::ToVec3() const
	{
		return { x, y, z };
	}
}