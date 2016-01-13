
// task2_serverView.cpp : Ctask2_serverView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "task2_server.h"
#endif

#include "task2_serverDoc.h"
#include "task2_serverView.h"
#include "DlgIP.h"
#include "MainFrm.h"
#include "ListenSocket.h"
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctask2_serverView

IMPLEMENT_DYNCREATE(Ctask2_serverView, CView)

BEGIN_MESSAGE_MAP(Ctask2_serverView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SEVER, &Ctask2_serverView::OnSever)
END_MESSAGE_MAP()

// Ctask2_serverView ����/����

HANDLE hThread;
DWORD ThreadID[50];                  //50����������

CString m_strServerIP;

int m_nServerPort;
char m_chHostName[200];     //������
char m_chBuff[1024]; 


CDlgIP *cdlgIP;

int g_connectCount=0;

void ThreadProcess(CSocket *cSocket);
Ctask2_serverView::Ctask2_serverView()
{
	// TODO: �ڴ˴���ӹ������

}

Ctask2_serverView::~Ctask2_serverView()
{
}

BOOL Ctask2_serverView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// Ctask2_serverView ����

void Ctask2_serverView::OnDraw(CDC* /*pDC*/)
{
	Ctask2_serverDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// Ctask2_serverView ��ӡ

BOOL Ctask2_serverView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void Ctask2_serverView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void Ctask2_serverView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// Ctask2_serverView ���

#ifdef _DEBUG
void Ctask2_serverView::AssertValid() const
{
	CView::AssertValid();
}

void Ctask2_serverView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctask2_serverDoc* Ctask2_serverView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctask2_serverDoc)));
	return (Ctask2_serverDoc*)m_pDocument;
}
#endif //_DEBUG


// Ctask2_serverView ��Ϣ�������


void Ctask2_serverView::OnSever()
{
	// TODO: �ڴ���������������
	
	cdlgIP=new CDlgIP();
	cdlgIP->Create(IDD_DIALOG_IP);
	cdlgIP->ShowWindow(SW_SHOW);
	UpdateData(TRUE);
	//if(cdlgIP.DoModal()==IDC_BUTTON_LISTEN)
	{
//		AfxSocketInit();
		UpdateData(FALSE);

		m_nServerPort=cdlgIP->m_nServerPort;

		BYTE m_bytServerIP[4];
		//m_bytServerIP=cDlgIP.m_dwServerIP;
		memcpy(m_bytServerIP,&(cdlgIP->m_dwServerIP),4);

		m_strServerIP.Format(_T("%u.%u.%u.%u"),m_bytServerIP[3],
			m_bytServerIP[2],m_bytServerIP[1],m_bytServerIP[0]);

		
	}

}
void ThreadProcess(CSocket *cSocket)
{

	/*char m_buf[1024];
	if (cSocket->Receive(m_buf,1024,0))
	{
		CString strMessage;

		strMessage.Format("�������ݣ�%s",m_buf);

		PostMessage(GetActiveWindow(),WM_UPDATEUI,0,(LPARAM)(LPCTSTR)strMessage);



	}*/

//	while (1)
		



}



afx_msg LRESULT Ctask2_serverView::OnUpdateUI(WPARAM wParam, LPARAM lParam)
{
	((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText((LPCTSTR)lParam);
	return 0;
}
