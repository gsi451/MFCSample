
// GSIClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CGSIClientApp:
// �� Ŭ������ ������ ���ؼ��� GSIClient.cpp�� �����Ͻʽÿ�.
//

class CGSIClientApp : public CWinApp
{
public:
	CGSIClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CGSIClientApp theApp;