#include "Canvas.h"

#include "Entities/GameObject.h"
#include "Settings/WndSettings.h"
#include "Globals/Clock.h"

EG::Canvas::Canvas()
{
	const float windowWidth = WndSettings::GetInstance().GetWndWidth();
	const float windowHeight = WndSettings::GetInstance().GetWndHeight();

	m_pQuad = GetGameObject()->CreateComponent<QuadComponent>();

	GetGameObject()->GetTransform()->scale.x = windowWidth / 2.0f;
	GetGameObject()->GetTransform()->scale.y = windowHeight / 2.0f;
	GetGameObject()->GetTransform()->position.x = -windowWidth / 4.0f;
	GetGameObject()->GetTransform()->position.y = windowHeight / 4.0f;
}

EG::Canvas::~Canvas()
{
	GetGameObject()->RemoveComponent<QuadComponent>();
}
