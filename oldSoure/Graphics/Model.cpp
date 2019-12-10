#include "Model.h"

EG::Model::Model()
{
	
}

EG::Model::~Model()
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
		delete m_meshes.at(i);

	m_meshes.clear();
}
