#pragma once

#include <chrono>

#include "Globals/Singleton.h"

namespace EG
{
	class Clock : public Singleton<Clock>
	{
	public:
		Clock();
		~Clock();

		void Update();

		const float& GetDeltaTime() const { return m_deltaTime; }
		const float& GetLifeTime() const { return m_lifeTime; };

		
	private:
		float m_deltaTime;
		float m_lifeTime;

		std::chrono::high_resolution_clock::time_point m_oldTimepoint;
		bool m_isFirst;
	};
}