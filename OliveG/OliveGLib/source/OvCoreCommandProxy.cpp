//#include "OvCoreCommandProxy.h"
//#include "OvCoreCommander.h"
//#include "OvVisibleText.h"
//#include "OvValueStream.h"
//#include "OvPoint2.h"
//
//#include "luabind/class.hpp"
//#include "luabind/detail/constructor.hpp"
//#include "luabind/luabind.hpp"
//using namespace luabind;
//
//OvSingleton_IMPL(OvCoreCommandProxy);
//
//struct OvCoreCommandProxy::OvPimple : OvMemObject
//{
//	OvVisibleTextSPtr	mCommandView;
//	string				mCommandString;
//};
//
//OvCoreCommandProxy::OvCoreCommandProxy()
//:m_pPimple(new OvCoreCommandProxy::OvPimple)
//{
//	OvVisibleTextSPtr	kpVisibleText = new OvVisibleText;
//	kpVisibleText->BuildFont("µ¸¿ò");
//	kpVisibleText->SetPosition(OvPoint2(0,0)) ;
//	kpVisibleText->SetWidth(500);
//	kpVisibleText->SetHeight(500);
//	m_pPimple->mCommandView = kpVisibleText;
//
//	OvCoreCommander::Instance()->ExcuteCommand("function ViewSetting(argView) end");
//
//	OvCoreCommander::Instance()->ExcuteCommand("function MessageListener(argMsg) end");
//
//	//luabind::call_function<int>(OvCoreCommander::Instance()->GetCoreLuaState(),"modify",kpVisibleText.GetRear());
//}
//
//OvCoreCommandProxy::~OvCoreCommandProxy()
//{
//
//}
//
//
//void		OvCoreCommandProxy::MessageListener(OvValueStream& rMessage)
//{
//	MSG kMsg;
//
//	OvVisibleTextSPtr	kpVisibleText = m_pPimple->mCommandView;
//	string strContext = kpVisibleText->GetText();
//	rMessage.PopStruct(kMsg);
//	switch (kMsg.message)
//	{
//	case WM_KEYDOWN :
//		{
//			switch (kMsg.wParam)
//			{
//			case VK_F5 : 
//				{
//					OvCoreCommander::Instance()->ExcuteCommand(strContext.data());
//				}
//				break;
//			case VK_F6 : 
//				{
//					luabind::call_function<int>(OvCoreCommander::Instance()->GetCoreLuaState(),"ViewSetting",kpVisibleText.GetRear());
//				}
//				break;
//			}
//		}
//		break;
//	case WM_CHAR :
//		{
//			switch (kMsg.wParam)
//			{
//			case VK_RETURN : 
//				{
//					strContext += "\n";
//				}
//				break;
//			case VK_BACK : 
//				{
//					if (strContext.size())
//					{
//						strContext.resize(strContext.size() - 1);
//					}
//				}
//				break;
//			case VK_ESCAPE : 
//				{
//					OvCoreCommander::Instance()->ExcuteCommand("OvExitProgram()");
//				}
//				break;
//			default :
//				{
//					strContext += (char)kMsg.wParam;
//				}
//				break;
//			}
//			kpVisibleText->SetText(strContext.data());
//		}
//		break;
//	}
//
//	luabind::call_function<int>(OvCoreCommander::Instance()->GetCoreLuaState(),"MessageListener",kMsg);
//
//}
//void		OvCoreCommandProxy::RenderCommandView()
//{
//	OvVisibleTextSPtr	kpVisibleText = m_pPimple->mCommandView;
//	if (kpVisibleText)
//	{
//		kpVisibleText->Render();
//	}
//}