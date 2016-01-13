
// task2_serverView.cpp : Ctask2_serverView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SEVER, &Ctask2_serverView::OnSever)
END_MESSAGE_MAP()

// Ctask2_serverView 构造/析构

HANDLE hThread;
DWORD ThreadID[50];                  //50个并发连接

CString m_strServerIP;

int m_nServerPort;
char m_chHostName[200];     //主机名
char m_chBuff[1024]; 


CDlgIP *cdlgIP;

int g_connectCount=0;

void ThreadProcess(CSocket *cSocket);
Ctask2_serverView::Ctask2_serverView()
{
	// TODO: 在此处添加构造代码

}

Ctask2_serverView::~Ctask2_serverView()
{
}

BOOL Ctask2_serverView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Ctask2_serverView 绘制

void Ctask2_serverView::OnDraw(CDC* /*pDC*/)
{
	Ctask2_serverDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// Ctask2_serverView 打印

BOOL Ctask2_serverView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Ctask2_serverView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Ctask2_serverView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// Ctask2_serverView 诊断

#ifdef _DEBUG
void Ctask2_serverView::AssertValid() const
{
	CView::AssertValid();
}

void Ctask2_serverView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctask2_serverDoc* Ctask2_serverView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctask2_serverDoc)));
	return (Ctask2_serverDoc*)m_pDocument;
}
#endif //_DEBUG


// Ctask2_serverView 消息处理程序


void Ctask2_serverView::OnSever()
{
	// TODO: 在此添加命令处理程序代码
	
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

		strMessage.Format("接收数据：%s",m_buf);

		PostMessage(GetActiveWindow(),WM_UPDATEUI,0,(LPARAM)(LPCTSTR)strMessage);



	}*/

//	while (1)
		



}



afx_msg LRESULT Ctask2_serverView::OnUpdateUI(WPARAM wParam, LPARAM lParam)
{
	((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText((LPCTSTR)lParam);
	return 0;
}
