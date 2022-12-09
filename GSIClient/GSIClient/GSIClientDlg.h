
// GSIClientDlg.h : ��� ����
//

#pragma once

#include "resource.h"

#include "ClientSocket.h"
#include "afxwin.h"


// CGSIClientDlg ��ȭ ����
class CGSIClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CGSIClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GSICLIENT_DIALOG };

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
  CClientSocket m_ClientSocket;
protected:
	afx_msg LRESULT OnClientRecv(WPARAM wParam, LPARAM lParam);

public:
	CEdit m_edit_send;
	CListBox m_list_msg;
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnDestroy();
};
