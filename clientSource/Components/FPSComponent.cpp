#include "FPSComponent.h"

#include "Entities/GameObject.h"
#include "Settings/WndSettings.h"
#include "Globals/Clock.h"

FPSComponent::FPSComponent()
{
	FT_Library library;

	FT_Init_FreeType( &library );

	//SetParent(pTestQuad);

	m_pTextComponent = GetGameObject()->CreateComponent<EG::TextComponent>("times.ttf");

	const float& rWindowWidth = EG::WndSettings::GetInstance().GetWndWidth();
	const float& rWindowHeight = EG::WndSettings::GetInstance().GetWndHeight();

	EG::Transform* pTransform = GetGameObject()->GetTransform();

	pTransform->position.x = -500.0f;
	pTransform->position.y = 80.0f;

	m_pTextComponent->SetText("Adrian Rondahl is the best!!!!!!");
	m_pTextComponent->SetFontSize(88);

	GetGameObject()->GetTransform()->rotation.z = 235.0f;

	m_pTextComponent->SetColor(EG::Color(0, 234.0f / 255.0f, 1.0f));

}

FPSComponent::~FPSComponent()
{
	GetGameObject()->RemoveComponent<EG::TextComponent>();
}

void FPSComponent::Update()
{
	//m_pTextComponent->SetText(m_pTextComponent->GetText() + 'd');

	/*const float& deltaTime = EG::Clock::GetInstance().GetDeltaTime();
	unsigned int currentFPS = 0;
	
	if (deltaTime != 0.0f)
		currentFPS = static_cast<int>(1.0f / deltaTime);
	else
		currentFPS = 0;

	EG::String fpsString = EG::String("FPS: ");
	fpsString += std::to_string(333).c_str();
	
	m_pTextComponent->SetText(fpsString);*/
}
