#pragma once
#include "gmath.h"

namespace GameEngine
{
	class Lighting
	{
	private:
		float _ambientStrength;
		gmath::vec3 _ambientColor;

		float _specularStrength;
		gmath::vec3 _lightColor;
		gmath::vec3 _lightPosition;	

	public:
		Lighting(const gmath::vec3& ambientColor, const float& ambientStrength, const gmath::vec3& pointLightColor, const gmath::vec3& pointLightPosition, const float& specularStrength);

		~Lighting();

		inline const gmath::vec3& GetLightColor() const { return _lightColor; }
		inline const gmath::vec3& GetLightPosition() const { return _lightPosition; }
		
		inline gmath::vec3 GetAmbientLight() const { return (_ambientColor * _ambientStrength); }
		inline const float& GetSpecStrength() const { return _specularStrength; }
		
		inline void SetLightColor(const gmath::vec3& lightColor) { _lightColor = lightColor; }
		inline void SetLightPos(const gmath::vec3& lightPosition) { _lightPosition = lightPosition; }
	};
}