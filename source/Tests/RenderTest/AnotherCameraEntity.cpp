#include "AnotherCameraEntity.h"

#include "Settings/WndSettings.h"

AnotherCameraEntity::AnotherCameraEntity()
{
	//float fov, float aspectRatio, float nearPlane, float farPlane, ProjectionType projectionType, Vector2D viewportStart, Vector2D viewportSize

	const float& windowHeight = EG::WndSettings::GetInstance().GetWndHeight();
	const float& windowWidth = EG::WndSettings::GetInstance().GetWndWidth();

	const float cameraHeight = 1080.0f / 4.0f;
	const float cameraWidth = 1920.0f / 4.0f;

	m_pCameraComponent = reinterpret_cast<EG::CameraComponent*>(EG::ComponentManager::GetInstance().CreateComponent<EG::CameraComponent>(
		m_id,
		45,
		windowWidth / windowHeight,
		1,
		1000,
		EG::CameraComponent::ProjectionType::Perspective,
		EG::Vector2D(windowWidth, windowHeight),
		EG::Vector2D(0.0f, 0.0f)));

	m_pCameraComponent->SetClearColor(EG::Color(0.3f, 0.3f, 0.3f));
	m_pCameraComponent->GetTransform().position.z = -5.0f;
	m_pCameraComponent->GetTransform().position.y = 2.5f;
	m_pCameraComponent->GetTransform().rotation.x = 25.0f;
}