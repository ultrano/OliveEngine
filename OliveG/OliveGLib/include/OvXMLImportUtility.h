#pragma once
#include "OvRefBase.h"
#include "OvMath.h"
#include <map>
OvREF_POINTER(OvMesh);
OvREF_POINTER(OvXObject);
OvREF_POINTER(OvXNode);
class TiXmlElement;

bool			OvXMLPoint3Import(TiXmlElement*,OvPoint3&);
bool			OvXMLQuaternionImport(TiXmlElement*,OvQuaternion&);
bool			OvXMLTransformInport(TiXmlElement*,OvTransform&);

OvMeshSPtr		OvXMLMeshImport(TiXmlElement*);

OvXObjectSPtr	OvXMLGeomImport(TiXmlElement*);

OvXObjectSPtr	OvXMLNodeImport(TiXmlElement*);

OvXObjectSPtr	OvXMLCameraImport(TiXmlElement*);

bool			 OvXMLNodeTableImport(TiXmlElement*,map<int,OvXObjectSPtr>& );
bool			 OvXMLGeomTableImport(TiXmlElement*,map<int,OvXObjectSPtr>& );
bool			 OvXMLCameraTableImport(TiXmlElement*,map<int,OvXObjectSPtr>& );

OvXObjectSPtr	OvXMLSceneNodeImport(TiXmlElement*);