#include "FBXLoader.h"

#include <iostream>
#include <string>
#include <Windows.h>

void EG::FBXLoader::Load(const String& rString)
{
	FbxManager* pSdkManager = FbxManager::Create();
	FbxIOSettings *ios = FbxIOSettings::Create(pSdkManager, IOSROOT);
	pSdkManager->SetIOSettings(ios);
	FbxImporter* pImporter = FbxImporter::Create(pSdkManager, "");

	assert(pImporter->Initialize(rString.GetString(), -1, pSdkManager->GetIOSettings()));

	FbxScene* pScene = FbxScene::Create(pSdkManager, "myScene");
	pImporter->Import(pScene);
	pImporter->Destroy();

	FbxNode* pRootNode = pScene->GetRootNode();
	if (pRootNode) {
		for (int i = 0; i < pRootNode->GetChildCount(); i++)
			PrintNode(pRootNode->GetChild(i));
	}
}

void EG::FBXLoader::PrintNode(FbxNode* pNode)
{
	String nodeName = pNode->GetName();
	FbxDouble3 translation = pNode->LclTranslation.Get();
	FbxDouble3 rotation = pNode->LclRotation.Get();
	FbxDouble3 scaling = pNode->LclScaling.Get();

	String printString = String("node name=") + nodeName.GetString()
		+ String(" translation='(") + translation[0] + String(", ") + translation[1] + String(", ") + translation[2] + String("')")
		+ String(" rotation='(") + rotation[0] + String(", ") + rotation[1] + String(", ") + rotation[2] + String("')")
		+ String(" scaling='(") + scaling[0] + String(", ") + scaling[1] + String(", ") + scaling[2] + String("')") + "\n";

	OutputDebugStringA(printString.GetString());

	for (int i = 0; i < pNode->GetNodeAttributeCount(); i++)
		PrintAttribute(pNode->GetNodeAttributeByIndex(i));

	for (int j = 0; j < pNode->GetChildCount(); j++)
		PrintNode(pNode->GetChild(j));
}

void EG::FBXLoader::PrintAttribute(FbxNodeAttribute* pAttribute)
{
	if (!pAttribute) return;

	String typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
	String attrName = pAttribute->GetName();

	String printString = String("attribute type=") + typeName.GetString() + String(" name=") + attrName.GetString() + "\n";

	OutputDebugStringA(printString.GetString());
}

EG::String EG::FBXLoader::GetAttributeTypeName(FbxNodeAttribute::EType type)
{
	switch (type) {
		case FbxNodeAttribute::eUnknown: return "unidentified";
		case FbxNodeAttribute::eNull: return "null";
		case FbxNodeAttribute::eMarker: return "marker";
		case FbxNodeAttribute::eSkeleton: return "skeleton";
		case FbxNodeAttribute::eMesh: return "mesh";
		case FbxNodeAttribute::eNurbs: return "nurbs";
		case FbxNodeAttribute::ePatch: return "patch";
		case FbxNodeAttribute::eCamera: return "camera";
		case FbxNodeAttribute::eCameraStereo: return "stereo";
		case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
		case FbxNodeAttribute::eLight: return "light";
		case FbxNodeAttribute::eOpticalReference: return "optical reference";
		case FbxNodeAttribute::eOpticalMarker: return "marker";
		case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
		case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
		case FbxNodeAttribute::eBoundary: return "boundary";
		case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
		case FbxNodeAttribute::eShape: return "shape";
		case FbxNodeAttribute::eLODGroup: return "lodgroup";
		case FbxNodeAttribute::eSubDiv: return "subdiv";
		default: return "unknown";
	}
}
