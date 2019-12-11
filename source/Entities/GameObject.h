#pragma once

#include "ECS/Entity.h"
#include "Components/Transform.h"
#include "Globals/Layer.h"

namespace EG
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		Transform* GetTransform() const { return m_pTransform; }
		
		Layer& Getlayer() { return m_layer; }
		void SetLayer(const Layer& rLayer) { m_layer = rLayer; }
		
	private:
		Transform* m_pTransform;
		Layer m_layer;
	};
	
}