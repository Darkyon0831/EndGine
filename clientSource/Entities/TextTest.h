#pragma once

#include "Entities/GameObject.h"
#include "Components/FPSComponent.h"

class TextTest : public EG::GameObject
{
public:
	TextTest();
	~TextTest();
	
private:
	FPSComponent* m_pFPSComponent;
};