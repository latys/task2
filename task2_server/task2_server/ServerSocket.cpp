#include "StdAfx.h"
#include "ServerSocket.h"
#include "DlgIP.h"


CServerSocket::CServerSocket(void)
{
}


CServerSocket::~CServerSocket(void)
{
}

void CServerSocket::OnReceive(int nErrorCode)
{
	char buf[1024]={0};
	
	int n=Receive(buf,1024);
	
	//
	CString m_str;
	m_str.Format("收到数据：%s\r\n",buf);
	HWND m_hwnd=FindWindow(NULL,_T("Dialog"));
	HWND m_hEdit=GetDlgItem(m_hwnd,IDC_EDIT_STATUS);
	
	//CDlgIP* cdlg=(CDlgIP *)CDlgIP::FromHandle(m_hwnd);
	AppendText(m_hEdit,m_str);
	//cdlg->GetDlgItem(IDC_EDIT_STATUS)->SetWindowText(m_str);
	
	CSocket::OnReceive(nErrorCode);
}
