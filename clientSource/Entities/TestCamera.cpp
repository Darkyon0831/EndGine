#include "TestCamera.h"
#include "Settings/WndSettings.h"

TestCamera::TestCamera()
{
	SetLayer(EG::Layer::LayerCamera);
	
	const float& windowHeight = EG::WndSettings::GetInstance().GetWndHeight();
	const float& windowWidth = EG::WndSettings::GetInstance().GetWndWidth();

	const float cameraHeight = 1080.0f / 4.0f;
	const float cameraWidth = 1920.0f / 4.0f;

	m_pCameraComponent = CreateComponent<EG::CameraComponent>(
		45,
		cameraWidth / cameraHeight,
		1,
		1000,
		EG::Vector2D(cameraWidth, cameraHeight),
		EG::Vector2D(-windowWidth / 2.0f + cameraWidth / 2.0f, windowHeight / 2.0f - cameraHeight / 2.0f));

	m_pCameraComponent->SetRenderLayerMask(EG::Layer::LayerCanvas);
	
	m_pCameraComponent->SetClearColor(EG::Color(0.6f, 0.6f, 0.6f));

	/*GetTransform()->position.z = -5.0f;
	GetTransform()->position.y = 2.5f;
	GetTransform()->rotation.x = 25.0f;*/
}

TestCamera::~TestCamera()
{
	RemoveComponent<EG::CameraComponent>();
}
