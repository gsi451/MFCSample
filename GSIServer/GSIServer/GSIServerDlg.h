
// GSIServerDlg.h : ��� ����
//

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "ServerSocket.h"

// CGSIServerDlg ��ȭ ����
class CGSIServerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CGSIServerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GSISERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
  CClientSocket *m_pClientSocket;
  CServerSocket *m_pServerSocket;

public:
	CListBox m_list_client;
	CListBox m_list_msg;
	CPtrList m_ptrClientSocketList; //For manage Client Sockets

protected:
	afx_msg LRESULT OnAcceptSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientMsgRecv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientClose(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void OnDestroy();
};
