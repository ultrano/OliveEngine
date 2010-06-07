#pragma once
#include "OvMemObject.h"
#include "OvRefBase.h"
#include "OvSingleton.h"
#include <map>
#include <string>
using namespace std;
OvREF_POINTER(OvObject);

class OvStorage;

class OvObjectFactory : public OvMemObject
{
	OvSingletonEx_DECL(OvObjectFactory);

public:

	OvObjectSPtr	CreateInstance(const string& rClass,OvStorage& rStorage);

private:

	typedef map<string,OvObjectSPtr (*)(OvStorage&)> tdFactoryCallback;
	tdFactoryCallback	m_mapFactoryCallback;

};



