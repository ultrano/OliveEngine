#pragma once

#include <map>
#include <list>

class OvAssociatedLinkConnector;
typedef std::list<OvAssociatedLinkConnector*> link_builder_list;

class OvObjectID;
class OvObject;
typedef std::map< OvObjectID, OvObject* > OvLinkageTable;