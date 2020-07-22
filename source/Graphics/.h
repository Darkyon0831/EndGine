#pragma once

#include <fbxsdk.h>
#include <Globals/String.h>

namespace EG
{
	class FBXLoader
	{
	public:

		void Load(const String& rString);
		void PrintNode(FbxNode* pNode);
		void PrintAttribute(FbxNodeAttribute* pAttribute);
		String GetAttributeTypeName(FbxNodeAttribute::EType type);

	private:
		FbxScene* m_pScene;
	};
}