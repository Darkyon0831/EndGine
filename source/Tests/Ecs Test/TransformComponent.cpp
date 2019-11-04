#include "TransformComponent.h"

TransformComponent::TransformComponent()
	: position(EG::Vector3D::Zero)
	, rotation(EG::Vector3D::Zero)
	, scale(EG::Vector3D(1.0f, 1.0f, 1.0f))
{
}
