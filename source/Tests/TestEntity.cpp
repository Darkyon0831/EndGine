#include "TestEntity.h"

EG::TestEntity::TestEntity()
{
	m_deltaTimeComponent = static_cast<DeltaTimeComponent*>(CreateComponent<DeltaTimeComponent>());

	int debug = 0;
}
