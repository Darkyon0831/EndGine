#include "GameObject.h"

EG::GameObject::GameObject()
{
	m_pTransform = CreateComponent<Transform>();
}

EG::GameObject::~GameObject()
{
	RemoveComponent<Transform>();
}
