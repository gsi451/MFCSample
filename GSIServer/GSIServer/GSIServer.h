
// GSIServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CGSIServerApp:
// �� Ŭ������ ������ ���ؼ��� GSIServer.cpp�� �����Ͻʽÿ�.
//

class CGSIServerApp : public CWinApp
{
public:
	CGSIServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CGSIServerApp theApp;