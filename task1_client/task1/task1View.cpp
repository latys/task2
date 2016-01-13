
// task1View.cpp : Ctask1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "task1.h"
#endif

#include "task1Doc.h"
#include "task1View.h"
#include "Bmp.h"
#include "DialogIP.h"
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctask1View

IMPLEMENT_DYNCREATE(Ctask1View, CView)

BEGIN_MESSAGE_MAP(Ctask1View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_OPEN, &Ctask1View::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &Ctask1View::OnFileSave)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_ADAPTSCREEN, &Ctask1View::OnAdaptScreen)
	ON_COMMAND(ID_ORIGINSIZE, &Ctask1View::OnOriginSize)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_CONNECT_SERVER, &Ctask1View::OnConnectServer)
END_MESSAGE_MAP()

// Ctask1View ����/����
CBmp g_cbmp;
float g_fZScaling=1;         //��¼������
CPoint g_ptMousePoint;       //��¼���λ��
float g_fXPositionInDC;      //��갴��ʱ��ȡ��ǰͼƬ��DC�е�λ�� 
float g_fYPositionInDC;
float g_fXoffset=0;            //����϶���X��ƫ����
float g_fYoffset=0;            //����϶���Y��ƫ����
int g_nwheelFlag=0;           //������ת����־��0��δת���� 1��ת��
int g_nLButtonDownFlag=0;     //���������±�־λ
int g_nMouseMoveFlag=0;       //����϶���־λ


Ctask1View::Ctask1View()
{
	// TODO: �ڴ˴���ӹ������

}

Ctask1View::~Ctask1View()
{
}

BOOL Ctask1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);

}

// Ctask1View ����

void Ctask1View::OnDraw(CDC* pDc/*pDC*/)
{
	Ctask1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(&rect);
	CBrush cBrush;
	cBrush.CreateSolidBrush(RGB(255,255,255));
	pDc->FillRect(rect,&cBrush);
	
	if (!g_nwheelFlag&&!g_nMouseMoveFlag)               //������δת��ʵ�ֵȱ���ʾ
	{
		CRect m_rc;
		CRect m_PicRc;             //ͼƬ�ȱ���������
		GetClientRect(&m_rc);
		float m_fRate=float(g_cbmp.m_bmpInfoHeader.biWidth)/float(g_cbmp.m_bmpInfoHeader.biHeight);
		
		float m_fRcRate=float(m_rc.Width())/float(m_rc.Height());


		if (m_fRate>=m_fRcRate)
		{

			g_cbmp.DrawCenter(this->m_hWnd, pDc->m_hDC, m_rc.Width(),int(m_rc.Width()/m_fRate));
			g_fZScaling=float(m_rc.Width())/g_cbmp.m_bmpInfoHeader.biWidth;
		}
		if (m_fRate<m_fRcRate)
		{

			g_cbmp.DrawCenter(this->m_hWnd, pDc->m_hDC,int(m_rc.Height()*m_fRate),m_rc.Height());
			g_fZScaling=float(m_rc.Height())/g_cbmp.m_bmpInfoHeader.biHeight;
		}
	}
	else  if(g_nwheelFlag==1)                         //������ת��ʵ�ַŴ���С
	{
		 g_cbmp.DrawCenter(this->m_hWnd, pDc->m_hDC, 
			               int(g_cbmp.m_bmpInfoHeader.biWidth*g_fZScaling),
			               int(g_cbmp.m_bmpInfoHeader.biHeight*g_fZScaling)
						   );
		 g_nwheelFlag=0;
	}
	if (g_nMouseMoveFlag==1)
	{
		int m_nXPosition;    //��ʼ��X������                                                        
		int m_nYPosition;    //��ʼ��Y������

		CRect m_rc;
		GetClientRect(&m_rc);

		m_nXPosition=g_fXPositionInDC+g_fXoffset;
		m_nYPosition=g_fYPositionInDC+g_fYoffset;

		g_cbmp.Draw(pDc->m_hDC,
			        m_nXPosition,
					m_nYPosition,
			        int(g_cbmp.m_bmpInfoHeader.biWidth*g_fZScaling), 
					int(g_cbmp.m_bmpInfoHeader.biHeight*g_fZScaling)
					);
		g_nMouseMoveFlag=0;
	}

	


	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}
void Ctask1View::GetPicRect(CImage img, CRect wdRect, CRect & rect)
{
	if (double(img.GetWidth())/double(img.GetHeight())>=double(wdRect.Width())/double(wdRect.Height()))
	{
//		rect.SetRect(0,0,wdRect.Width(),img.GetHeight()/(img.GetHeight()/))
	}

}
void Ctask1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Ctask1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Ctask1View ���

#ifdef _DEBUG
void Ctask1View::AssertValid() const
{
	CView::AssertValid();
}

void Ctask1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctask1Doc* Ctask1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctask1Doc)));
	return (Ctask1Doc*)m_pDocument;
}
#endif //_DEBUG


// Ctask1View ��Ϣ�������


void Ctask1View::OnFileOpen()
{
	// TODO: �ڴ���������������
	
	HRESULT m_hResult;
	m_lpbImageDataSrc.Destroy();
	CFileDialog m_dlg(0,0,0,0,0,NULL);
	if (m_dlg.DoModal()==IDOK)
	{
		CString m_str=m_dlg.GetPathName();
	
		if (!g_cbmp.IsNull())
		{
			g_cbmp.ReleaseBmp();
		}
		g_cbmp.LoadBmp(m_str);
	
	}
	Invalidate(false); 

	
}


void Ctask1View::OnFileSave()
{
	// TODO: �ڴ���������������
	CString m_filter="*.jpg|*.png|*.bmp";
	CFileDialog m_dlg(0,0,0,0,m_filter,0);
	if(m_dlg.DoModal()==IDOK)
	{
		CString m_str=m_dlg.GetPathName();
		g_cbmp.SaveBmp(m_str);

	}
	
}


BOOL Ctask1View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	 g_nwheelFlag=1;
	 
	 g_fZScaling+= 0.05*(zDelta/120); 

	 if (g_fZScaling>=2)
	 {
		 g_fZScaling=2;
	 }
	 if (g_fZScaling<=0.1)
	 {
		 g_fZScaling=0.1;
	 }


	 {
		 Invalidate(false);
	 }
	 return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void Ctask1View::OnAdaptScreen()
{
	// TODO: �ڴ���������������
	
	Invalidate(false);
}


void Ctask1View::OnOriginSize()
{
	// TODO: �ڴ���������������
	CClientDC dc(this);
	g_cbmp.DrawCenter(this->m_hWnd,dc.m_hDC,g_cbmp.m_bmpInfoHeader.biWidth, g_cbmp.m_bmpInfoHeader.biHeight);
	g_fZScaling=1;
}


int Ctask1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	/*RECT rect = {0,0,20,500};
	m_cScrollBar.Create(WS_CHILD | WS_VISIBLE | SB_VERT,rect,this,2);//WS_VISIBLEһ��Ҫ���ϣ���Ȼ��Ϳ�����m_scrollbar��
	m_cScrollBar.SetScrollRange(0,1);
	m_cScrollBar.SetScrollPos(50);
	// TODO:  �ڴ������ר�õĴ�������*/

	return 0;
}


void Ctask1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (g_nLButtonDownFlag==1)
	{
		g_fXoffset=point.x-g_ptMousePoint.x;
		g_fYoffset=point.y-g_ptMousePoint.y;
		g_nMouseMoveFlag=1;
		Invalidate(false);
	}
	CView::OnMouseMove(nFlags, point);
}


void Ctask1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	g_nLButtonDownFlag=0;
	CView::OnLButtonUp(nFlags, point);
}


void Ctask1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	g_nLButtonDownFlag=1;
	g_ptMousePoint=point;
	g_fXPositionInDC=g_cbmp.get_m_fXPositionInDC();
	g_fYPositionInDC=g_cbmp.get_m_fYPositionInDC();
	CView::OnLButtonDown(nFlags, point);
}


BOOL Ctask1View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CView::OnEraseBkgnd(pDC);
	//return TRUE;
}


void Ctask1View::OnConnectServer()
{
	// TODO: �ڴ���������������
	CDialogIP cDlgIP;
	if (cDlgIP.DoModal()==IDOK)
	{
		UpdateData(TRUE);
		AfxSocketInit();
		CSocket m_socket;
		CString m_strServerIP;
		int m_nServerPort;

		char m_chBuff[1024];
		BYTE m_bytServerIP[4];
		//m_bytServerIP=cDlgIP.m_dwServerIP;
		memcpy(m_bytServerIP,&cDlgIP.m_dwServerIP,4);

		m_strServerIP.Format(_T("%u.%u.%u.%u"),m_bytServerIP[3],m_bytServerIP[2],m_bytServerIP[1],m_bytServerIP[0]);
		m_nServerPort=atoi(cDlgIP.m_strServerPort);
		if (!m_socket.Socket())
		{
			AfxMessageBox("SOCKET ����ʧ��");
			return;
		}

		if (m_socket.Connect(m_strServerIP,m_nServerPort))
		{
			AfxMessageBox("connect success");
			if (m_socket.Receive(m_chBuff,sizeof(m_chBuff),0))
			{
				if(strcmp(m_chBuff,"connect success")==0)
					AfxMessageBox("connect success");
			}

		}
		else
		{
			AfxMessageBox("����ʧ��");
		}

		
		
	}
	

}
