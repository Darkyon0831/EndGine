#include "TextTest.h"
#include "Settings/WndSettings.h"

TextTest::TextTest()
{
	SetLayer(EG::Layer::LayerCanvas);
	//SetParent(pTestQuad);

	m_pFPSComponent = CreateComponent<FPSComponent>();
}

TextTest::~TextTest()
{
	RemoveComponent<FPSComponent>();
}
