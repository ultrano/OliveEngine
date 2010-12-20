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


OvBool OvObjectID::operator==(const OvObjectID& idRef){return core == idRef.core;};
OvBool OvObjectID::operator==(OvObjectID& idRef){return core == idRef.core;};

OvBool OvObjectID::operator!=(const OvObjectID& idRef){return core != idRef.core;};
OvBool OvObjectID::operator!=(OvObjectID& idRef){return core != idRef.core;};

OvBool OvObjectID::operator<(const OvObjectID& idRef){return core < idRef.core;};
OvBool OvObjectID::operator<(OvObjectID& idRef){return core < idRef.core;};

OvBool OvObjectID::operator>(const OvObjectID& idRef){return core > idRef.core;};
OvBool OvObjectID::operator>(OvObjectID& idRef){return core > idRef.core;};

OvBool operator==(const OvObjectID& idRef0, const OvObjectID& idRef1){return idRef0.core == idRef1.core;};
OvBool operator==( OvObjectID& idRef0,  OvObjectID& idRef1){return idRef0.core == idRef1.core;};

OvBool operator!=(const OvObjectID& idRef0, const OvObjectID& idRef1){return idRef0.core != idRef1.core;};
OvBool operator!=( OvObjectID& idRef0,  OvObjectID& idRef1){return idRef0.core != idRef1.core;};

OvBool operator<(const OvObjectID& idRef0, const OvObjectID& idRef1){return idRef0.core < idRef1.core;};

OvBool operator>(const OvObjectID& idRef0, const OvObjectID& idRef1){return idRef0.core > idRef1.core;};
