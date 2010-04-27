#include "OvCoreCommander.h"
#include "OvLua.h"

#include "luabind/class.hpp"
#include "luabind/detail/constructor.hpp"
#include "luabind/luabind.hpp"
using namespace luabind;

#include "OvTexture.h"
#include "OvVisibleText.h"
#include "OvMath.h"
#include "OvTransform.h"
#include "OvObject.h"
#include "OvXObject.h"
#include "OvXNode.h"


OvSingleton_IMPL(OvCoreCommander);
struct SPrivateStruct_ExitHandle
{
	SPrivateStruct_ExitHandle():bCheck(false){};
	bool	bCheck;
};
static SPrivateStruct_ExitHandle g_PrivateValue_hExitHandle;
bool	OvExitProgram()
{
	return g_PrivateValue_hExitHandle.bCheck;
}
void	OvPrivateFunction_OvExitProgram()
{
	g_PrivateValue_hExitHandle.bCheck = true;
}
bool	OvPrivateFunction_OvExcuteScriptFile(const char* pFilePath)
{
	return OvCoreCommander::Instance()->ExcuteScriptFile(pFilePath);
}

struct OvCoreCommander::OvPimple : OvMemObject
{
	OvLua	mLua;
};

OvCoreCommander::OvCoreCommander()
:m_pPimple(OvNew OvCoreCommander::OvPimple)
{
}
OvCoreCommander::~OvCoreCommander()
{

}
void		Initialize_CoreHandling()
{
	OvCoreCommander::Instance()->Initialize();
}
bool		ExcuteCommand_CoreHandling(const char* pCommand)
{
	return OvCoreCommander::Instance()->ExcuteCommand(pCommand);
}
void		OvCoreCommander::Initialize()
{
	luabind::open(GetCoreLuaState());
	luabind::module(GetCoreLuaState(),"OvCoreCommander")
		[
			def("Initialize",Initialize_CoreHandling)
			,def("ExcuteCommand",ExcuteCommand_CoreHandling)
		];
	luabind::module(GetCoreLuaState())
		[
			class_<OvObject>("OvObject")
			.def(constructor<>())
			.def("SetName",&OvObject::SetName)
			.def("GetName",&OvObject::GetName)
// 			.def("SetDescription",&OvObject::SetDescription)
// 			.def("GetDescription",&OvObject::GetDescription)
			.def("GetObjectID",&OvObject::GetObjectID)
			,
			class_<OvXObject,OvObject>("OvXObject")
			.def(constructor<>())
			.def("Update",				&OvXObject::Update)
			.def("UpdateSubordinate",	&OvXObject::UpdateSubordinate)
			.def("SetTranslate",		(void(OvXObject::*)(OvPoint3&))&OvXObject::SetTranslate)
			.def("SetTranslate",		(void(OvXObject::*)(float,float,float))&OvXObject::SetTranslate)
			.def("SetRotation",			&OvXObject::SetRotation)
			.def("SetScale",			(void(OvXObject::*)(float))&OvXObject::SetScale)
			.def("SetScale",			(void(OvXObject::*)(const OvPoint3&))&OvXObject::SetScale)
			.def("GetTranslate",		&OvXObject::GetTranslate)
			.def("GetRotation",			&OvXObject::GetRotation)
			.def("GetScale",			&OvXObject::GetScale)
			.def("GetWorldTranslate",	&OvXObject::GetWorldTranslate)
			.def("GetWorldRotation",	&OvXObject::GetWorldRotation)
			.def("GetWorldScale",		&OvXObject::GetWorldScale)
			.def("GetWorldTransform",	&OvXObject::GetWorldTransform)
			.def("IsNode",				&OvXObject::IsNode)
			.def("IsLeaf",				&OvXObject::IsLeaf)
			.def("GetParent",			&OvXObject::GetParent)
			,
			class_<OvVisibleText>("OvVisibleText")
			.def(constructor<>())
			.def("BuildFont",			&OvVisibleText::BuildFont)
			.def("SetAlignHorizon",		&OvVisibleText::SetAlignHorizon)
			.def("SetAlignVertical",	&OvVisibleText::SetAlignVertical)
			.def("GetAlignHorizon",		&OvVisibleText::GetAlignHorizon)
			.def("GetAlignVertical",	&OvVisibleText::GetAlignVertical)
			.def("SetText",				&OvVisibleText::SetText)
			.def("GetText",				&OvVisibleText::GetText)
			.def("SetTextColor",		&OvVisibleText::SetTextColor)
			.def("SetPosition",			(void(OvVisibleText::*)(OvPoint2&))&OvVisibleText::SetPosition)
			.def("SetPosition",			(void(OvVisibleText::*)(float,float))&OvVisibleText::SetPosition)
			.def("SetWidth",			&OvVisibleText::SetWidth)
			.def("SetHeight",			&OvVisibleText::SetHeight)
			.def("GetPosition",			&OvVisibleText::GetPosition)
			.def("GetWidth",			&OvVisibleText::GetWidth)
			.def("GetHeight",			&OvVisibleText::GetHeight)
			.def("GetRect",				&OvVisibleText::GetRect)
			.def("SetItalicStyle",		&OvVisibleText::SetItalicStyle)
			.def("SetAutoLineFeed",		&OvVisibleText::SetAutoLineFeed)
			.def("Render",				&OvVisibleText::Render)
			.def("RenderToTexture",		&OvVisibleText::RenderToTexture)
			,
			def("OvMessageBox",&OvMessageBox)
			,
			def("OvExitProgram",OvPrivateFunction_OvExitProgram)
			,
			def("OvExcuteScriptFile",&OvPrivateFunction_OvExcuteScriptFile)
			,
			class_<MSG>("MSG")
			.property("hwnd",&MSG::hwnd)
			.property("message",&MSG::message)
			.property("wParam",&MSG::wParam)
			.property("lParam",&MSG::lParam)
			.property("time",&MSG::time)
			.property("pt",&MSG::pt)
			,
			class_<POINT>("POINT")
			.property("x",&POINT::x)
			.property("y",&POINT::y)
		];

}

lua_State*	OvCoreCommander::GetCoreLuaState()
{
	return m_pPimple->mLua.GetScriptContext();
}
bool		OvCoreCommander::ExcuteCommand(const char* pCommand)
{
	if (pCommand)
	{
		return m_pPimple->mLua.RunString(pCommand);
	}
	return false;
}
bool		OvCoreCommander::ExcuteScriptFile(const char* pFilePath)
{
	if (pFilePath)
	{
		return m_pPimple->mLua.RunScript(pFilePath);
	}
	return false;
}