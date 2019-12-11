#include "IComponent.h"

EG::GameObject* EG::IComponent::GetGameObject() const
{
	return reinterpret_cast<GameObject*>(m_pEntity);
}
