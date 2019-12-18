#include "GameObject.h"

EG::GameObject::GameObject()
	: m_layer(Layer::LayerVisual)
	, m_pParent(nullptr)
{
	m_pTransform = CreateComponent<Transform>();

	int i = 0;
}

EG::GameObject::~GameObject()
{
	RemoveComponent<Transform>();
}

EG::Transform* EG::GameObject::GetTransform() const
{
	return m_pTransform;
}
