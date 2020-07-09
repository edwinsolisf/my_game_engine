#include "Camera.h"

namespace GameEngine
{
	Camera::Camera()
		:_Target(0.0f,0.0f,-1.0f), _pitch(0.0f), _yaw(0.0f)
	{
		SetCamera(_Position, _Target);
	}

	Camera::Camera(const gmath::vec3 & position, const gmath::vec3 & target)
		:_Position(position), _Target(target)
	{
		SetCamera(position, target);
	}

	Camera::~Camera()
	{
	}

	void Camera::SetCamera(const gmath::vec3& position, const gmath::vec3& target, const gmath::vec3& up)
	{
		_Position = position;
		_Target = target;

		_Direction = gmath::normalize(_Target - _Position);
		_CameraRight = gmath::normalize(up.CrossProduct(_Direction));
		_CameraUp = gmath::normalize(_Direction.CrossProduct(_CameraRight));

		float a[] =
		{
			_CameraRight.x, _CameraRight.y, _CameraRight.z, 0.0f,
			_CameraUp.x, _CameraUp.y, _CameraUp.z, 0.0f,
			_Direction.x, _Direction.y, _Direction.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		gmath::mat4 mat(a);
		_View = mat*gmath::translate(-_Position);
	}
	void Camera::MoveForward(const float & step)
	{
		SetCamera(_Position + _Direction * step, _Target + _Direction * step);
	}
	void Camera::MoveRight(const float & step)
	{
		SetCamera(_Position + _CameraRight * step, _Target + _CameraRight * step);
	}
	void Camera::MoveUp(const float & step)
	{
		SetCamera(_Position + _CameraUp * step, _Target + _CameraUp * step);
	}
	void Camera::RotatePitch(const float & angle)
	{
		gmath::vec4 ans = gmath::rotate(-angle, _CameraRight) * gmath::vec4(_Direction, 0.0f);
		SetCamera(_Position, (ans.ToVec3()*_Target.Magnitude()) + _Position);
	}
	void Camera::RotateYaw(const float & angle)
	{
		gmath::vec4 ans = gmath::rotate(angle, _CameraUp) * gmath::vec4(_Direction, 0.0f);
		SetCamera(_Position, (ans.ToVec3()*_Target.Magnitude()) + _Position);
	}
	void Camera::RotateRoll(const float & angle)
	{
		gmath::vec4 ans = gmath::rotate(-angle, _Direction) * gmath::vec4(_CameraUp, 0.0f);
		SetCamera(_Position, _Target, ans.ToVec3());
	}
}