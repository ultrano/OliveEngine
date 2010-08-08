#pragma once

#include <map>
#include <list>

class OvRelationLinkBuilder;
typedef std::list<OvRelationLinkBuilder*> link_builder_list;

class OvObjectID;
class OvObject;
typedef std::map< OvObjectID, OvObject* > restore_object_table;