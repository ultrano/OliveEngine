#pragma once
//
//-------------------------------------------------------------------
//
#define OvSTL_Find(__Container,__Value) (std::find(__Container.begin(),__Container.end(),__Value))
//
//-------------------------------------------------------------------
//
#define OvDllImport __declspec(dllimport)
#define OvDllExport __declspec(dllexport)
//
//-------------------------------------------------------------------
//

//
//-------------------------------------------------------------------
//
#ifdef	OvExportDll
#define	OvClassDllType __declspec(dllexport)
#else
#define	OvClassDllType __declspec(dllimport)
#endif
//
//-------------------------------------------------------------------
//
#define InterfaceClass
//
//-------------------------------------------------------------------
//
#ifdef	_DEBUG
#define OvOutputDebugStr(__Value)	OutputDebugString(__Value)
#else
#define OvOutputDebugStr(__Value)
#endif
//
//-------------------------------------------------------------------
//
#define OvSafeDelete(__Pointer) if(__Pointer){delete __Pointer;}
//
//-------------------------------------------------------------------
//
//! 이녀석은 Assert로 바꾸자
#define OvError(__add_msg)		OvErrorMsgBox(__FILE__,__FUNCTION__,__LINE__,__add_msg)
#define OvAssert(__exp__) ((!!(__exp__)) || (OvErrorMsgBox(__FILE__,__FUNCTION__,__LINE__,#__exp__),0), __exp__)
//
//-------------------------------------------------------------------
//
#define OvGOTO_END_PROCESS goto __end_process_line_in_block;
#define OvIMPL_END_PROCESS	__end_process_line_in_block:
//
//-------------------------------------------------------------------
//
#define Length3D(_x1,_y1,_z1,_x2,_y2,_z2) (sqrtf(powf((_x1-_x2),2) + powf((_y1-_y2),2) + powf((_z1-_z2),2)))
#define Length2D(_x1,_y1,_x2,_y2) (sqrtf(powf(_x1-_x2,2) + powf(_y1-_y2,2)))
//
//-------------------------------------------------------------------
//
#define OvPimple_DESC(ClassName) OvREF_POINTER(OvPimple);OvPimpleSPtr
#define OvPimple_IMPL(ClassName) class ClassName::OvPimple
