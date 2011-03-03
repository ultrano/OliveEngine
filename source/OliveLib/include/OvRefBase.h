#pragma once
#include "OvUtility.h"
#include "OvMemObject.h"
#include "OvSmartPointer.h"
#include "OvWeakPointer.h"
#define OvREF_POINTER(__class_name)	class __class_name;\
	typedef OvSmartPointer<__class_name>	__class_name##SPtr;\
	typedef OvWeakPointer<__class_name>	__class_name##WPtr;

// 클레스 이름 : OvRefBase
// 설명 : 
//		가장 기본이 된다.
//		Olive에서 사용하는 대부분의 클레스들은 스마트포인터를 이용한 
//		포인터 참조카운팅 시스템을 사용한다.
//		그렇기 때문에 OvRefBase를 상속받은 클레스들은
//		OvSmartPointerf와 매크로로 만들어진
//		"클레스이름Ptr"이라는 템플릿 포인터를
//		사용하길 권장한다. (예, OvXNode는 OvXNodePtr라는 템플리포인터와 한쌍.)
//		"클레스이름Ptr"를 사용한다면, 
//		사용자는 생성한 클레스를 delete해줄 필요가 없이
//		사용하는 포인터 가운트가 0이되면 자동으로 삭제 된다.
//		(정확히 말하면 delete해줄 필요가 없는게 아니라 해선 안된다.)
//		중요한건 "클레스이름Ptr"를 이용하기로 했다면 절대 delete는 사용해선 
//		안된다는 것이다.
//		"클레스이름Ptr"가 알아서 삭제해줘야할 메모리를 임의삭제한다면
//		"클레스이름Ptr"가 삭제된포인터에 대해 다시 delete를 호출하기때문에
//		예측못한 메모리관련 에러가 발생할것이다.

// 사용설명서 : 
//		"클레스이름Ptr"는 클레스 맴버변수나
//		지역변수로 사용하더라도 그 지역안에 있을때는 삭제되길 바라지 않을시에만 사용하면 된다.
//		함수의 인자로 쓸때에는 "클레스이름Ptr"와 "클레스이름*" 둘다 사용해도 되지만
//		인자값과같이 생명주기가 짧은곳에는 "클레스이름*"를 대신 사용해도 된다.
class  OvRefBase : public OvMemObject
{
	friend class OvRefCounter;
	OvRTTI_DECL_ROOT(OvRefBase);
public:
	// 일단 생성되면서 카운티을 0으로 맞춘다.
	OvRefBase();

	OvRefCounter* GetRefCounter();

private:
	
	void	DeleteThis(){OvDelete this;};

protected:

	// 소멸될때 아직 누군가 사용중이라 카운트가 0이 아닌 상태라면
	// 잘못된 삭제요청으로 간주하고 에러메세지를 뛰우고 
	// 강제 종료한다. (멀리봤을때 처음 잘못된 삭제가 요청됬을때 잡아주는게 좋다고 생각해서다.)
	virtual ~OvRefBase();
private:
	OvRefCounter*	m_reference_counter;
};

