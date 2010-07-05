#pragma once
#include "OvMemObject.h"
#include "OvRefBase.h"
#include "OvSingleton.h"
#include <map>
#include <string>
using namespace std;
OvREF_POINTER(OvObject);

class OvStorage;
class OvObjectID;

class OvObjectFactory : public OvSingletonBase< OvObjectFactory >
{

public:
	OvObjectFactory();
	~OvObjectFactory();
	OvObjectSPtr	CreateInstance(const string& rClass);

private:

	typedef map<string,OvObjectSPtr (*)(OvObjectID&)> tdFactoryCallback;
	tdFactoryCallback	m_mapFactoryCallback;

};



