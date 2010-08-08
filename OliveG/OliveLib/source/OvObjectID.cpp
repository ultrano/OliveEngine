#include "OvObjectID.h"

OvObjectID	OvObjectID::INVALID(0);

OvObjectID::OvObjectID( id_core_type copyid)
:core(copyid)
{
}
OvObjectID::OvObjectID()
:core(OvObjectID::INVALID.core)
{

}
OvObjectID::OvObjectID( OvObjectID& copyid)
:core(copyid.core)
{

}
OvObjectID::OvObjectID( const OvObjectID& copyid)
:core(copyid.core)
{

}
OvObjectID::~OvObjectID()
{

}


bool OvObjectID::operator==(const OvObjectID& idRef){return core == idRef.core;};
bool OvObjectID::operator==(OvObjectID& idRef){return core == idRef.core;};

bool OvObjectID::operator!=(const OvObjectID& idRef){return core != idRef.core;};
bool OvObjectID::operator!=(OvObjectID& idRef){return core != idRef.core;};

bool OvObjectID::operator<(const OvObjectID& idRef){return core < idRef.core;};
bool OvObjectID::operator<(OvObjectID& idRef){return core < idRef.core;};

bool OvObjectID::operator>(const OvObjectID& idRef){return core > idRef.core;};
bool OvObjectID::operator>(OvObjectID& idRef){return core > idRef.core;};

bool operator==(const OvObjectID& idRef0, const OvObjectID& idRef1){return idRef0.core == idRef1.core;};
bool operator==( OvObjectID& idRef0,  OvObjectID& idRef1){return idRef0.core == idRef1.core;};

bool operator!=(const OvObjectID& idRef0, const OvObjectID& idRef1){return idRef0.core != idRef1.core;};
bool operator!=( OvObjectID& idRef0,  OvObjectID& idRef1){return idRef0.core != idRef1.core;};

bool operator<(const OvObjectID& idRef0, const OvObjectID& idRef1){return idRef0.core < idRef1.core;};

bool operator>(const OvObjectID& idRef0, const OvObjectID& idRef1){return idRef0.core > idRef1.core;};