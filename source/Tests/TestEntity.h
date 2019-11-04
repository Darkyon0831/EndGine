#pragma once

#include "ECS/Entity.h"
#include "Tests/DeltaTimeComponent.h"

namespace EG
{
	class TestEntity : public Entity
	{
	public:
		TestEntity();
		~TestEntity() = default;

	private:
		DeltaTimeComponent* m_deltaTimeComponent;
	};
}