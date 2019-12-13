#include "TextTest.h"

TextTest::TextTest(TestQuad* pTestQuad)
{
	SetLayer(EG::Layer::LayerCanvas);
	SetParent(pTestQuad);

	m_pTextComponent = CreateComponent<EG::TextComponent>();
}

TextTest::~TextTest()
{
	RemoveComponent<EG::TextComponent>();
}
