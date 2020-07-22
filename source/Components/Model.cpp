#include "Model.h"

EG::Model::Model()
{
}

EG::Model::~Model()
{
}

void EG::Model::ClearMeshes()
{
	for (int i = 0; i < m_meshAssets.size(); i++)
		delete m_meshAssets.at(i);

	m_meshAssets.clear();
}
