
// task2_serverView.h : Ctask2_serverView 类的接口
//

#pragma once

#define  WM_UPDATEUI (WM_USER+100)
class Ctask2_serverView : public CView
{
protected: // 仅从序列化创建
	Ctask2_serverView();
	DECLARE_DYNCREATE(Ctask2_serverView)

// 特性
public:
	Ctask2_serverDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~Ctask2_serverView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    afx_msg LRESULT OnUpdateUI(WPARAM wParam, LPARAM lParam);
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSever();
};

#ifndef _DEBUG  // task2_serverView.cpp 中的调试版本
inline Ctask2_serverDoc* Ctask2_serverView::GetDocument() const
   { return reinterpret_cast<Ctask2_serverDoc*>(m_pDocument); }
#endif

