#include "DefaultCamera.h"
#include "Settings/WndSettings.h"

EG::DefaultCamera::DefaultCamera()
{
	SetLayer(Layer::LayerCamera);
	
	const float& windowHeight = WndSettings::GetInstance().GetWndHeight();
	const float& windowWidth = WndSettings::GetInstance().GetWndWidth();

	m_pCamera = CreateComponent<CameraComponent>(
		45,
		windowWidth / windowHeight,
		-1,
		1000,
		EG::Vector2D(windowWidth, windowHeight),
		EG::Vector2D(0, 0));

	m_pCamera->SetRenderLayerMask(Layer::LayerVisual);

	m_pCamera->SetClearColor(EG::Color(0.0f, 0.0f, 0.0f));
	GetTransform()->position.z = -10.0f;
	//GetTransform()->position.y = 2.5f;
	//GetTransform()->position.x = -2.0f;
	//GetTransform()->rotation.x = 25.0f;
}

EG::DefaultCamera::~DefaultCamera()
{
	RemoveComponent<CameraComponent>();
}
