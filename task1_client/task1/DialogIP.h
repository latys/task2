#pragma once
#include "afxcmn.h"


// CDialogIP 对话框

class CDialogIP : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogIP)

public:
	CDialogIP(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogIP();

// 对话框数据
	enum { IDD = IDD_DIALOG_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_IPAddServerIP;
	CString m_strServerPort;
	DWORD m_dwServerIP;
};
