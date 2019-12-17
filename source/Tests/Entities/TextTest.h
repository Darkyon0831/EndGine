#pragma once

#include "Entities/GameObject.h"
#include "Tests/Components/FPSComponent.h"

class TextTest : public EG::GameObject
{
public:
	TextTest();
	~TextTest();
	
private:
	FPSComponent* m_pFPSComponent;
};