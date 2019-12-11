#pragma once

#include "GameObject.h"
#include "Components/CameraComponent.h"

namespace EG
{
	class DefaultCamera : public GameObject
	{
	public:
		DefaultCamera();
		virtual ~DefaultCamera();

		CameraComponent* GetCamera() const { return m_pCamera; }
		
	private:
		CameraComponent* m_pCamera;
	};
}