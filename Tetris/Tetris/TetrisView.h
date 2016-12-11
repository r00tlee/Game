
// TetrisView.h : CTetrisView 클래스의 인터페이스
//

#pragma once

#include "TetrisInfo.h"
#include "TetrisBGM.h"

class CTetrisView : public CView
{
protected: // serialization에서만 만들어집니다.
	CTetrisView();
	DECLARE_DYNCREATE(CTetrisView)

// 특성입니다.
public:
	CTetrisDoc* GetDocument() const;

// 작업입니다.
public:
	CTetrisInfo* m_CTetrisInfo;
	CTetrisBGM* m_CTetrisBGM;
	int m_state;
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
	virtual ~CTetrisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // TetrisView.cpp의 디버그 버전
inline CTetrisDoc* CTetrisView::GetDocument() const
   { return reinterpret_cast<CTetrisDoc*>(m_pDocument); }
#endif

