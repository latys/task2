
// task2_serverView.h : Ctask2_serverView ��Ľӿ�
//

#pragma once

#define  WM_UPDATEUI (WM_USER+100)
class Ctask2_serverView : public CView
{
protected: // �������л�����
	Ctask2_serverView();
	DECLARE_DYNCREATE(Ctask2_serverView)

// ����
public:
	Ctask2_serverDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~Ctask2_serverView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    afx_msg LRESULT OnUpdateUI(WPARAM wParam, LPARAM lParam);
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSever();
};

#ifndef _DEBUG  // task2_serverView.cpp �еĵ��԰汾
inline Ctask2_serverDoc* Ctask2_serverView::GetDocument() const
   { return reinterpret_cast<Ctask2_serverDoc*>(m_pDocument); }
#endif

