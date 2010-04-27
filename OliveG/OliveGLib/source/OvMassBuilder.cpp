#include "OvMassBuilder.h"
#include "OvNodeBuilder.h"
#include "OvNodeTreeBuilder.h"
#include "OvXNode.h"
#include "tinyxml.h"
#include "OvXMLImportUtility.h"

OvXNodeSPtr OvMassBuilder::Build(const char* pFile)
{
	TiXmlDocument	kDoc("NodeBuild");

	if (kDoc.LoadFile(pFile))
	{
		TiXmlElement*	kpRoot = kDoc.FirstChildElement("SceneExport");
		return OvXMLSceneNodeImport(kpRoot);
		/*if (kpRoot)
		{
			string kstrDirectory = OvGetDirectoryInFullFilePath(pFile);
			int kiExportCount = 0;
			kpRoot->Attribute("NodeCount",&kiExportCount);
			TiXmlElement*	kpEle = NULL;
			OvNodeBuilder	kNodeBuilder;
			OvXNodeSPtr kpRootNode = new OvXNode;
			
			if (kpRootNode)
			{
				OvNodeTreeBuilderSPtr kpNodeTreeBuilder = new OvNodeTreeBuilder;
				kpEle = kpRoot->FirstChildElement("ExportNode");
				for (int i = 0 ; (kpEle)&&(i < kiExportCount) ; ++i,kpEle = kpEle->NextSiblingElement())
				{
					string kstrFIle = kstrDirectory + string(kpEle->Attribute("File"));
					SNodeInheritInfo kpElementNodeInfo = kNodeBuilder.BuildNodeInfo(kstrFIle.data());
					kpNodeTreeBuilder->AddElementObject(kpElementNodeInfo);
				}
				kpRootNode->AttachChild(kpNodeTreeBuilder->Build());
				return kpRootNode;
			}
		}*/
	}

	return NULL;
}