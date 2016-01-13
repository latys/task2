// DialogIP.cpp : 实现文件
//

#include "stdafx.h"
#include "task1.h"
#include "DialogIP.h"
#include "afxdialogex.h"


// CDialogIP 对话框

IMPLEMENT_DYNAMIC(CDialogIP, CDialogEx)

CDialogIP::CDialogIP(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogIP::IDD, pParent)
	, m_strServerPort(_T(""))
	, m_dwServerIP(0)
{

}

CDialogIP::~CDialogIP()
{
}

void CDialogIP::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPAddServerIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_strServerPort);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, m_dwServerIP);
}


BEGIN_MESSAGE_MAP(CDialogIP, CDialogEx)
END_MESSAGE_MAP()


// CDialogIP 消息处理程序
