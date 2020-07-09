#pragma once
#include "gmath.h"

namespace GameEngine
{
	class Camera
	{
	private:
		gmath::vec3 _Position;
		gmath::vec3 _Target;

		gmath::vec3 _Direction;
		gmath::vec3 _CameraUp;
		gmath::vec3 _CameraRight;

		gmath::mat4 _View;

		float _pitch;
		float _yaw;
	public:
		Camera();
		Camera(const gmath::vec3& position, const gmath::vec3& target);
		~Camera();

		void SetCamera(const gmath::vec3& position, const gmath::vec3& target, const gmath::vec3& = gmath::posY);

		void MoveForward(const float& step);
		void MoveRight(const float& step);
		void MoveUp(const float& step);

		void RotatePitch(const float& angle);
		void RotateYaw(const float& angle);
		void RotateRoll(const float& angle);

		inline void SetYaw(const float& angle) { _yaw = angle; }
		inline void SetPitch(const float& angle) { _pitch = angle; }

		inline const float& GetYaw() const { return _yaw; }
		inline const float& GetPitch() const { return _pitch; }

		inline const gmath::vec3& GetPosition() const { return _Position; }
		inline const gmath::vec3& GetTarget() const { return _Target; }
		inline const gmath::vec3& GetDirection() const { return _Direction; }
		inline const gmath::vec3& GetRight() const { return _CameraRight; }
		inline const gmath::vec3& GetUp() const { return _CameraUp; }
		inline const gmath::mat4& GetView() const { return _View; }
	};

}