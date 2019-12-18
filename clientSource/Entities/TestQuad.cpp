#include "TestQuad.h"

TestQuad::TestQuad()
{
	SetLayer(EG::Layer::LayerCanvas);
	
	m_pCanvas = CreateComponent<EG::Canvas>();
}

TestQuad::~TestQuad()
{
	RemoveComponent<EG::Canvas>();
}
