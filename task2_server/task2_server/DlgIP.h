#pragma once
#include "resource.h"

// CDlgIP �Ի���
void AppendText(HWND hEditWnd, LPCTSTR Text);

class CDlgIP : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgIP)

public:
	CDlgIP(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgIP();

// �Ի�������
	enum { IDD = IDD_DIALOG_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
