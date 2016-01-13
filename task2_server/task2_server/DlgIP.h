#pragma once
#include "resource.h"

// CDlgIP 对话框
void AppendText(HWND hEditWnd, LPCTSTR Text);

class CDlgIP : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgIP)

public:
	CDlgIP(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgIP();

// 对话框数据
	enum { IDD = IDD_DIALOG_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	DWORD m_dwServerIP;
	CString m_strServerPort;
	int m_nServerPort;

	void onAccept(CString str);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnBnClickedButtonListen();
	afx_msg void OnClickedButtonListen();
	afx_msg void OnClickedButtonStoplisten();
};
