#pragma once

#include "ECS/Component.h"
#include "Components/TextComponent.h"

#include <ft2build.h>
#include FT_FREETYPE_H

class FPSComponent : public EG::Component<FPSComponent>
{
public:

	FPSComponent();
	~FPSComponent();

	void Update() override;

private:
	EG::TextComponent* m_pTextComponent;
};