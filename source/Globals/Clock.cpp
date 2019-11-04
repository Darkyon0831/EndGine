#include "Clock.h"

EG::Clock::Clock()
	: m_deltaTime(0.0)
	, m_lifeTime(0.0f)
	, m_isFirst(true)
{
	
}

EG::Clock::~Clock()
{
	
}

void EG::Clock::Update()
{
	if (m_isFirst)
	{
		m_oldTimepoint = std::chrono::high_resolution_clock::now();
		m_isFirst = false;
	}
	else
	{
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(now - m_oldTimepoint);

		m_deltaTime = timeSpan.count();

		m_oldTimepoint = now;

		m_lifeTime += m_deltaTime;
	}
}
