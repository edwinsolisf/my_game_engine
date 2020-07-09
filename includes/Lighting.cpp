#include "Lighting.h"

namespace GameEngine
{
	Lighting::Lighting(const gmath::vec3 & ambientColor, const float & ambientStrength, const gmath::vec3 & pointLightColor, const gmath::vec3 & pointLightPosition, const float& specularStrength)
		:_ambientColor(ambientColor), _ambientStrength(ambientStrength), _lightColor(pointLightColor), _lightPosition(pointLightPosition), _specularStrength(specularStrength)
	{
	}

	Lighting::~Lighting()
	{
	}
}