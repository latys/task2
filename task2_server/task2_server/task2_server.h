
// task2_server.h : task2_server Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// Ctask2_serverApp:
// �йش����ʵ�֣������ task2_server.cpp
//

class Ctask2_serverApp : public CWinApp
{
public:
	Ctask2_serverApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ctask2_serverApp theApp;
