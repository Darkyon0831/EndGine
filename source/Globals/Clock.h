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
		
	private:
		float m_deltaTime;

		std::chrono::high_resolution_clock::time_point m_oldTimepoint;
		bool m_isFirst;
	};
}