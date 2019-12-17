#pragma once

#include "ECS/Component.h"
#include "Components/TextComponent.h"

class FPSComponent : public EG::Component<FPSComponent>
{
public:
	FPSComponent();
	~FPSComponent();

	void Update() override;

private:
	EG::TextComponent* m_pTextComponent;
};