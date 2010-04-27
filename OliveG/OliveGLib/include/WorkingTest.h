
// -------------------------------------- 애니메이션을 위한 
// -------------------------------------- 키와 값에 대한 인터포레이터를 만드려 했으나, 범용성을 위한 추상화가 아직 
// -------------------------------------- 제대로 확립되지가 못해서 작업을 중단 한다. 추후 주먹구구 작업이 진행된후
// -------------------------------------- 필요한 부분과 불필요한 부분, 공통 부분과 비 공통 부분에 대한 
// -------------------------------------- 명확한 경계선이 그어지면 그때부터 분리하는 과정을 거쳐 인터포레이터라는
// -------------------------------------- 개념으로서 때어낼 것이다.
// -------------------------------------- 이렇게 분리된 인터포레이터는 애니메이션뿐만 아닌 (보간자)로서 다목적으로 사용될것이다.

//#pragma once 
//#include "OvRefBase.h"
//
////OvREF_POINTER(OvInterpolator)
//
//class OvInterpolator : OvMemObject
//{
//public:
//	enum eInterpolatorType
//	{
//		eInterpolatorType_Linear,
//	};
//	int GetType();
//protected:
//	OvInterpolator(eInterpolatorType eType);
//
//private:
//	//! Member Values (Ensconsed for encapsulation)
//	//! Application can access member only using get,set interface
//	struct OvPimple;
//	OvAutoPtr<OvPimple> m_pPimple;
//};

//class OvLinearInterpolator : public OvInterpolator
//{
//public :
//	OvLinearInterpolator();
//};