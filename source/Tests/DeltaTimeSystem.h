#pragma once

#include "ECS/System.h"
#include <chrono>

class DeltaTimeSystem : public EG::System<DeltaTimeSystem>
{
public:
	void PreStart() override;
	void PreUpdate() override;

private:
	float m_deltaTime;

	std::chrono::high_resolution_clock::time_point m_oldTimepoint;
	bool m_isFirst;
};
