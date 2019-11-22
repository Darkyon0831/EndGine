#include "CameraEntity.h"

#include "Settings/WndSettings.h"

CameraEntity::CameraEntity() : Entity()
{
	//float fov, float aspectRatio, float nearPlane, float farPlane, ProjectionType projectionType, Vector2D viewportStart, Vector2D viewportSize

	const float& windowHeight = EG::WndSettings::GetInstance().GetWndHeight();
	const float& windowWidth = EG::WndSettings::GetInstance().GetWndWidth();
	
	m_pCameraComponent = reinterpret_cast<EG::CameraComponent*>(EG::ComponentManager::GetInstance().CreateComponent<EG::CameraComponent>(
		m_id, 45, windowWidth / windowHeight, 0, 1000, EG::CameraComponent::ProjectionType::Perspective,
		EG::Vector2D(0, 0), EG::Vector2D(windowWidth, windowHeight)));

	//m_pCameraComponent2 = reinterpret_cast<EG::CameraComponent*>(EG::ComponentManager::GetInstance().CreateComponent<EG::CameraComponent>(
	//	m_id, 45.0f, 495.0f / 270.0f, 1, 1000, EG::CameraComponent::ProjectionType::Perspective,
	//	EG::Vector2D(1485.0f, 0.0f), EG::Vector2D(495.0f, 270.0f)));


	//rgb(64, 64, 64)
	m_pCameraComponent->SetClearColor(EG::Color(0.0f, 0.0f, 0.0f));
	m_pCameraComponent->GetTransform().position.z = -5.0f;
	//m_pCameraComponent->GetTransform().position.y = 2.5f;
	//m_pCameraComponent->GetTransform().rotation.x = 25.0f;

	//m_pCameraComponent2->SetClearColor(EG::Color(64.0f / 256.0f, 64.0f / 256.0f, 64.0f / 256.0f));
	//m_pCameraComponent2->GetTransform().position.z = -5.0f;
	//m_pCameraComponent2->GetTransform().position.y = 2.5f;
	//m_pCameraComponent2->GetTransform().rotation.x = 25.0f;
}
