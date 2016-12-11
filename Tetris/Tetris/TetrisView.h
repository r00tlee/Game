
// TetrisView.h : CTetrisView Ŭ������ �������̽�
//

#pragma once

#include "TetrisInfo.h"
#include "TetrisBGM.h"

class CTetrisView : public CView
{
protected: // serialization������ ��������ϴ�.
	CTetrisView();
	DECLARE_DYNCREATE(CTetrisView)

// Ư���Դϴ�.
public:
	CTetrisDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	CTetrisInfo* m_CTetrisInfo;
	CTetrisBGM* m_CTetrisBGM;
	int m_state;
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CTetrisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // TetrisView.cpp�� ����� ����
inline CTetrisDoc* CTetrisView::GetDocument() const
   { return reinterpret_cast<CTetrisDoc*>(m_pDocument); }
#endif

