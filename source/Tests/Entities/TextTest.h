#pragma once

#include "Entities/GameObject.h"
#include "Components/TextComponent.h"
#include "TestQuad.h"

class TextTest : public EG::GameObject
{
public:
	TextTest(TestQuad* pTestQuad);
	~TextTest();
	
private:
	EG::TextComponent* m_pTextComponent;
};