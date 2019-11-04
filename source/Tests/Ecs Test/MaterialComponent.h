#pragma once

#include "Graphics/Shader.h"
#include "Globals/Texture.h"

class MaterialComponent
{
public:
	EG::Shader* pShader;
	EG::Texture* pColorMap;
};