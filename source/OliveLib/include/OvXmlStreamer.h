#pragma once
#include "OvMemObject.h"
#include "OvUtility.h"

// �� Ŭ������ ������ ���� ������ �������� ����
// �ֿ켱���� �Ѵ�. �׸�ŭ �������� ���� �������̽���
// ������ �������� ��߳��� �ִ� �������� �����ϴ� ������ �Ѵ�.
// PowerShell ������ Xml �� �ٷ�� ������ ���� �ο��ϱ�� �ߴ�.
class OvXmlStreamer : public OvMemObject
{
	OvRTTI_DECL_ROOT(OvXmlStreamer);

public:

	OvXmlStreamer( std::string& file );
	virtual ~OvXmlStreamer();



private:


};