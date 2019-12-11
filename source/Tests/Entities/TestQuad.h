#pragma once

#include "Entities/GameObject.h"
#include "Components/Canvas.h"

class TestQuad : public EG::GameObject
{
public:
	TestQuad();
	~TestQuad();
	
private:
	EG::Canvas* m_pCanvas;
};