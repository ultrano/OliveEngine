#pragma once
#include "OvUtility.h"
#include "OvMemObject.h"
#include "OvSmartPointer.h"
#include "OvWeakPointer.h"
#define OvREF_POINTER(__class_name)	class __class_name;\
	typedef OvSmartPointer<__class_name>	__class_name##SPtr;\
	typedef OvWeakPointer<__class_name>	__class_name##WPtr;

// Ŭ���� �̸� : OvRefBase
// ���� : 
//		���� �⺻�� �ȴ�.
//		Olive���� ����ϴ� ��κ��� Ŭ�������� ����Ʈ�����͸� �̿��� 
//		������ ����ī���� �ý����� ����Ѵ�.
//		�׷��� ������ OvRefBase�� ��ӹ��� Ŭ��������
//		OvSmartPointerf�� ��ũ�η� �������
//		"Ŭ�����̸�Ptr"�̶�� ���ø� �����͸�
//		����ϱ� �����Ѵ�. (��, OvXNode�� OvXNodePtr��� ���ø������Ϳ� �ѽ�.)
//		"Ŭ�����̸�Ptr"�� ����Ѵٸ�, 
//		����ڴ� ������ Ŭ������ delete���� �ʿ䰡 ����
//		����ϴ� ������ ����Ʈ�� 0�̵Ǹ� �ڵ����� ���� �ȴ�.
//		(��Ȯ�� ���ϸ� delete���� �ʿ䰡 ���°� �ƴ϶� �ؼ� �ȵȴ�.)
//		�߿��Ѱ� "Ŭ�����̸�Ptr"�� �̿��ϱ�� �ߴٸ� ���� delete�� ����ؼ� 
//		�ȵȴٴ� ���̴�.
//		"Ŭ�����̸�Ptr"�� �˾Ƽ� ����������� �޸𸮸� ���ǻ����Ѵٸ�
//		"Ŭ�����̸�Ptr"�� �����������Ϳ� ���� �ٽ� delete�� ȣ���ϱ⶧����
//		�������� �޸𸮰��� ������ �߻��Ұ��̴�.

// ��뼳�� : 
//		"Ŭ�����̸�Ptr"�� Ŭ���� �ɹ�������
//		���������� ����ϴ��� �� �����ȿ� �������� �����Ǳ� �ٶ��� �����ÿ��� ����ϸ� �ȴ�.
//		�Լ��� ���ڷ� �������� "Ŭ�����̸�Ptr"�� "Ŭ�����̸�*" �Ѵ� ����ص� ������
//		���ڰ������� �����ֱⰡ ª�������� "Ŭ�����̸�*"�� ��� ����ص� �ȴ�.
class  OvRefBase : public OvMemObject
{
	friend class OvRefCounter;
	OvRTTI_DECL_ROOT(OvRefBase);
public:
	// �ϴ� �����Ǹ鼭 ī��Ƽ�� 0���� �����.
	OvRefBase();

	OvRefCounter* GetRefCounter();

private:
	
	void	DeleteThis(){OvDelete this;};

protected:

	// �Ҹ�ɶ� ���� ������ ������̶� ī��Ʈ�� 0�� �ƴ� ���¶��
	// �߸��� ������û���� �����ϰ� �����޼����� �ٿ�� 
	// ���� �����Ѵ�. (�ָ������� ó�� �߸��� ������ ��û������ ����ִ°� ���ٰ� �����ؼ���.)
	virtual ~OvRefBase();
private:
	OvRefCounter*	m_reference_counter;
};

