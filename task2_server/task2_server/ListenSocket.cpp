#include "StdAfx.h"
#include "ListenSocket.h"
#include "DlgIP.h"


CListenSocket::CListenSocket(void)
{
}


CListenSocket::~CListenSocket(void)
{
}
void CListenSocket::OnAccept(int nErrorCode)
{
	CServerSocket *temp=new CServerSocket() ;
	Accept(*temp);

	HWND m_hwnd=FindWindow(NULL,_T("Dialog"));
	CDlgIP* cdlg=(CDlgIP *)CDlgIP::FromHandle(m_hwnd);
	HWND m_hEdit=GetDlgItem(m_hwnd,IDC_EDIT_STATUS);
	AppendText(m_hEdit,"连接成功\r\n");
	//cdlg->GetDlgItem(IDC_EDIT_STATUS)->SetWindowText("连接成功");
	//onAccept("连接成功");
	temp->Send("success",7,0);
	CSocket::OnAccept(nErrorCode);
}


