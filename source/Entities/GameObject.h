#pragma once

#include "ECS/Entity.h"
#include "Components/Transform.h"

namespace EG
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		Transform* GetTransform() const { return m_pTransform; }
		
	private:
		Transform* m_pTransform;
	};
	
}