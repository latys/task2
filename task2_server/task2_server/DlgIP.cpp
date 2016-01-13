// DlgIP.cpp : 实现文件
//

#include "stdafx.h"
#include "task2_server.h"
#include "DlgIP.h"
#include "afxdialogex.h"
#include <afxsock.h>
#include "ListenSocket.h"


// CDlgIP 对话框

IMPLEMENT_DYNAMIC(CDlgIP, CDialogEx)



CListenSocket m_socket;

CDlgIP::CDlgIP(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgIP::IDD, pParent)
	, m_dwServerIP(0)
	, m_strServerPort(_T(""))
{

}

CDlgIP::~CDlgIP()
{
}

void CDlgIP::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_IPAddress(pDX, IDC_SERVERIP, m_dwServerIP);
	DDX_Text(pDX, IDC_SERVERPORT, m_nServerPort);
}


BEGIN_MESSAGE_MAP(CDlgIP, CDialogEx)
	ON_WM_CREATE()
	//ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CDlgIP::OnBnClickedButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CDlgIP::OnClickedButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_STOPLISTEN, &CDlgIP::OnClickedButtonStoplisten)
END_MESSAGE_MAP()


// CDlgIP 消息处理程序
int CDlgIP::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	AfxSocketInit();
	char m_chHostName[200];     //主机名
	gethostname(m_chHostName,200);
	HOSTENT *host=gethostbyname(m_chHostName);    //主机信息
	if (host==NULL)
	{
		AfxMessageBox("获取主机信息失败");
		return 0;
	}
	char * m_chServerIP=inet_ntoa(*(in_addr *)host->h_addr_list[0]);
	DWORD dwTemp;

	dwTemp=inet_addr(m_chServerIP);
	char * temp=(char *)&dwTemp;
	char tempIP[4];
	for (int i=0;i<4;i++)
	{
		tempIP[i]=temp[3-i];
	}

	memcpy(&(m_dwServerIP),tempIP,4);
	m_nServerPort=8080;

	this->GetDlgItem(IDC_BUTTON_STOPLISTEN)->EnableWindow(FALSE);

	//	UpdateData(FALSE);

	return 0;
}




void CDlgIP::OnClickedButtonListen()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_socket.Create(8080))
	{
		AfxMessageBox("socket 建立失败");
		return;
	}
	else
	{
		BOOL m_bOptVal=TRUE;
		m_socket.SetSockOpt(SO_REUSEADDR,&m_bOptVal,sizeof(m_bOptVal),SOL_SOCKET);
		if(m_socket.Listen(5))
		{
			this->GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
			this->GetDlgItem(IDC_BUTTON_STOPLISTEN)->EnableWindow(TRUE);

			
			HWND m_hEdit;
			m_hEdit=::GetDlgItem(this->m_hWnd,IDC_EDIT_STATUS);
			AppendText(m_hEdit,"开始监听\r\n");
			//this->GetDlgItem(IDC_EDIT_STATUS)->SetWindowText("正在监听");
		}

	}

}


void CDlgIP::OnClickedButtonStoplisten()
{
	// TODO: 在此添加控件通知处理程序代码
	m_socket.Close();
	this->GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_BUTTON_STOPLISTEN)->EnableWindow(FALSE);

	HWND m_hEdit;
	m_hEdit=::GetDlgItem(this->m_hWnd,IDC_EDIT_STATUS);
	AppendText(m_hEdit,"停止监听\r\n");
}

void CDlgIP::onAccept(CString str)
{
	this->GetDlgItem(IDC_BUTTON_STOPLISTEN)->SetWindowText(str);
}

void AppendText(HWND hEditWnd, LPCTSTR Text)
{
	int idx = GetWindowTextLength(hEditWnd);
	SendMessage(hEditWnd, EM_SETSEL, (WPARAM)idx, (LPARAM)idx);
	SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)Text);
}