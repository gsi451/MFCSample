
// GSIClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "GSIClient.h"
#include "GSIClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IP _T("192.168.1.163")
#define PORT 9900

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGSIClientDlg ��ȭ ����




CGSIClientDlg::CGSIClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGSIClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGSIClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SEND, m_edit_send);
	DDX_Control(pDX, IDC_LIST_MSG, m_list_msg);
}

BEGIN_MESSAGE_MAP(CGSIClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CGSIClientDlg::OnBnClickedBtnSend)
	ON_MESSAGE(WM_CLIENT_RECV, &CGSIClientDlg::OnClientRecv)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CGSIClientDlg �޽��� ó����

BOOL CGSIClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	WSADATA wsadata;
	WSAStartup(0x0202, &wsadata);  // ws2_32. Dll �� ����ϱ� ���� �ʱ�ȭ �Ѵ�.

	m_ClientSocket.SetWnd(this->m_hWnd);
	m_ClientSocket.Create();

	if(m_ClientSocket.Connect(IP, PORT) == FALSE) {

		int err = m_ClientSocket.GetLastError();

		CString msg;
		msg.Format(_T("Err:%d"), err);
		AfxMessageBox(msg);
		
		AfxMessageBox(_T("ERROR : Failed to connect Server"));
		PostQuitMessage(0);

		return FALSE;
	}

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CGSIClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CGSIClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CGSIClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGSIClientDlg::OnBnClickedBtnSend()
{
	CString str;
	LPCTSTR lpctstr;

	UpdateData(TRUE);

	m_edit_send.GetWindowTextW(str);
	lpctstr = (LPCTSTR)str;

	//m_ClientSocket.Send((LPVOID)(LPCTSTR)str,str.GetLength() *2);

	m_ClientSocket.Send(lpctstr, lstrlen(lpctstr) *2);

	m_edit_send.SetWindowTextW(_T(""));

	UpdateData(FALSE);
}

afx_msg LRESULT CGSIClientDlg::OnClientRecv(WPARAM wParam, LPARAM lParam)
{
  LPCTSTR lpszStr = (LPCTSTR)lParam;
 
  m_list_msg.InsertString(-1,lpszStr);
  m_list_msg.SetCurSel(m_list_msg.GetCount()-1);
	return 0;
}


void CGSIClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	WSACleanup();  // ws2_32.dll �� ����� �ߴ��Ѵ�.
}
