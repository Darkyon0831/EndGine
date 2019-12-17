#include "FPSComponent.h"

#include "Entities/GameObject.h"
#include "Settings/WndSettings.h"
#include "Globals/Clock.h"

FPSComponent::FPSComponent()
{
	//SetParent(pTestQuad);

	m_pTextComponent = GetGameObject()->CreateComponent<EG::TextComponent>();

	const float& rWindowWidth = EG::WndSettings::GetInstance().GetWndWidth();
	const float& rWindowHeight = EG::WndSettings::GetInstance().GetWndHeight();

	EG::Transform* pTransform = GetGameObject()->GetTransform();

	pTransform->position.x = -rWindowWidth / 2.0f + 6.0f;
	pTransform->position.y = rWindowHeight / 2.0f - 16.0f / 2.0f - 6.0f;

	m_pTextComponent->SetText("FPS: ");
}

FPSComponent::~FPSComponent()
{
	GetGameObject()->RemoveComponent<EG::TextComponent>();
}

void FPSComponent::Update()
{
	const float& deltaTime = EG::Clock::GetInstance().GetDeltaTime();
	unsigned int currentFPS = 0;
	
	if (deltaTime != 0.0f)
		currentFPS = static_cast<int>(1.0f / deltaTime);
	else
		currentFPS = 0;

	EG::String fpsString = EG::String("FPS: ");
	fpsString += std::to_string(currentFPS).c_str();
	
	m_pTextComponent->SetText(fpsString);
}
