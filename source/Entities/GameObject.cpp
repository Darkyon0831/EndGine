#include "GameObject.h"

EG::GameObject::GameObject()
	: m_layer(Layer::LayerVisual)
{
	m_pTransform = CreateComponent<Transform>();
}

EG::GameObject::~GameObject()
{
	RemoveComponent<Transform>();
}
