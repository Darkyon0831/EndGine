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

		Transform* GetTransform() const;
		
		Layer& Getlayer() { return m_layer; }
		void SetLayer(const Layer& rLayer) { m_layer = rLayer; }

		GameObject* GetParent() const { return m_pParent; }
		void SetParent(GameObject* pParent) { m_pParent = pParent; }

		void AddChild(GameObject* pChild) { m_childs.push_back(pChild); }
		GameObject* GetChild(const int index) { return m_childs.at(index); }
		int GetTotalChilds() const { return m_childs.size(); }
		
	private:
		Transform* m_pTransform;
		Layer m_layer;
		
		GameObject* m_pParent;
		std::vector<GameObject*> m_childs;	
	};
	
}