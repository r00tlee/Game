
// PoketMonsterView.h : CPoketMonsterView Ŭ������ �������̽�
//

#pragma once
#include "PoketMonsterMap.h"
#include "Player.h"

class CPoketMonsterView : public CView
{
protected: // serialization������ ��������ϴ�.
	CPoketMonsterView();
	DECLARE_DYNCREATE(CPoketMonsterView)

// Ư���Դϴ�.
public:
	CPoketMonsterDoc* GetDocument() const;

// �۾��Դϴ�.
public:
//	CPoketMonsterRoot* m_cPoketMonsterRoot;
	CPoketMonsterMap* m_cPoketMonsterMap;
	CPlayer* m_cPlayer;
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
	virtual ~CPoketMonsterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // PoketMonsterView.cpp�� ����� ����
inline CPoketMonsterDoc* CPoketMonsterView::GetDocument() const
   { return reinterpret_cast<CPoketMonsterDoc*>(m_pDocument); }
#endif

