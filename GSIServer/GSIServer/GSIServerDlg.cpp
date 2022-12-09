
// GSIServerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "GSIServer.h"
#include "GSIServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PORT 9900   //������ ��Ʈ ����

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


// CGSIServerDlg ��ȭ ����




CGSIServerDlg::CGSIServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGSIServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGSIServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CLIENT, m_list_client);
	DDX_Control(pDX, IDC_LIST_MSG, m_list_msg);
}

BEGIN_MESSAGE_MAP(CGSIServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_ACCEPT_SOCKET, &CGSIServerDlg::OnAcceptSocket)
	ON_MESSAGE(WM_CLIENT_MSG_RECV, &CGSIServerDlg::OnClientMsgRecv)
	ON_MESSAGE(WM_CLIENT_CLOSE, &CGSIServerDlg::OnClientClose)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CGSIServerDlg �޽��� ó����

BOOL CGSIServerDlg::OnInitDialog()
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

	WSADATA wsadata;
	WSAStartup(0x0202, &wsadata);  // ws2_32. Dll �� ����ϱ� ���� �ʱ�ȭ �Ѵ�.

	//Listen ���� �ʱ�ȭ
	m_pServerSocket = new CServerSocket;
	m_pServerSocket->SetWnd(this->m_hWnd);
 
	//���� Listen�ϱ�
	m_pServerSocket->Create(PORT);
	m_pServerSocket->Listen();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CGSIServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGSIServerDlg::OnPaint()
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
HCURSOR CGSIServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


afx_msg LRESULT CGSIServerDlg::OnAcceptSocket(WPARAM wParam, LPARAM lParam)
{
  CString str;
  m_pClientSocket = (CClientSocket*) lParam;
  m_ptrClientSocketList.AddTail(m_pClientSocket);
 
  str.Format(_T("Client (%d)"), (int)(m_pClientSocket));
	m_list_client.InsertString(-1,str);
 
  m_pClientSocket = NULL;
  delete m_pClientSocket;

	return 0;
}


afx_msg LRESULT CGSIServerDlg::OnClientMsgRecv(WPARAM wParam, LPARAM lParam)
{
  LPCTSTR lpszStr = (LPCTSTR)lParam;
 
  //BroadCasting
  POSITION pos = m_ptrClientSocketList.GetHeadPosition();
  
  while(pos != NULL)
  {
    CClientSocket* pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
    if(pClient!=NULL)
    {
      //UNICODE ����ϸ� ���� �޸�ũ�� *2 �ؾ���
      //Client�� Broadcasting�ϱ�
      pClient->Send(lpszStr, lstrlen(lpszStr) * 2);
    }
  }
 
  //m_list_msg�� �޽��� �߰�
  m_list_msg.InsertString(-1,lpszStr);
  m_list_msg.SetCurSel(m_list_msg.GetCount()-1);

	return 0;
}


afx_msg LRESULT CGSIServerDlg::OnClientClose(WPARAM wParam, LPARAM lParam)
{
  CClientSocket *pClient = (CClientSocket *)lParam;
  CString str;
  UINT idx=0;
  POSITION pos = m_ptrClientSocketList.Find(pClient);
 
  if(pos!=NULL)
  {
    //m_list_client���� �ش� Client ����
    str.Format(_T("Client (%d)"), (int)pClient);
    idx = m_list_client.SelectString(-1, (LPCTSTR)str);
    m_list_client.DeleteString(idx);
     
    //CPtrList������ �ش� Client ����
    m_ptrClientSocketList.RemoveAt(pos);
  }

	return 0;
}


void CGSIServerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	WSACleanup();  // ws2_32.dll �� ����� �ߴ��Ѵ�.
}
