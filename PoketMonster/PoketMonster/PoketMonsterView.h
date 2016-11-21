
// PoketMonsterView.h : CPoketMonsterView 클래스의 인터페이스
//

#pragma once
#include "PoketMonsterMap.h"
#include "Player.h"

class CPoketMonsterView : public CView
{
protected: // serialization에서만 만들어집니다.
	CPoketMonsterView();
	DECLARE_DYNCREATE(CPoketMonsterView)

// 특성입니다.
public:
	CPoketMonsterDoc* GetDocument() const;

// 작업입니다.
public:
//	CPoketMonsterRoot* m_cPoketMonsterRoot;
	CPoketMonsterMap* m_cPoketMonsterMap;
	CPlayer* m_cPlayer;
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CPoketMonsterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // PoketMonsterView.cpp의 디버그 버전
inline CPoketMonsterDoc* CPoketMonsterView::GetDocument() const
   { return reinterpret_cast<CPoketMonsterDoc*>(m_pDocument); }
#endif

