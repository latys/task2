#pragma once
#include "afxcmn.h"


// CDialogIP �Ի���

class CDialogIP : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogIP)

public:
	CDialogIP(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogIP();

// �Ի�������
	enum { IDD = IDD_DIALOG_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_IPAddServerIP;
	CString m_strServerPort;
	DWORD m_dwServerIP;
};
