
// PoketMonsterView.cpp : CPoketMonsterView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "PoketMonster.h"
#endif

#include "PoketMonsterDoc.h"
#include "PoketMonsterView.h"

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPoketMonsterView

IMPLEMENT_DYNCREATE(CPoketMonsterView, CView)

BEGIN_MESSAGE_MAP(CPoketMonsterView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CPoketMonsterView 생성/소멸

CPoketMonsterView::CPoketMonsterView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CPoketMonsterView::~CPoketMonsterView()
{
	delete m_cPlayer;
	delete m_cPoketMonsterMap;
}

BOOL CPoketMonsterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPoketMonsterView 그리기

void CPoketMonsterView::OnDraw(CDC* pDC)
{
	CPoketMonsterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	m_cPoketMonsterMap->Draw();
	m_cPlayer->Draw();
	pDC->BitBlt(0, 0, 1920, 1080, &(m_cPlayer->m_bufCDC), 0, 0, SRCCOPY);
}

// CPoketMonsterView 인쇄

BOOL CPoketMonsterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPoketMonsterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPoketMonsterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPoketMonsterView 진단

#ifdef _DEBUG
void CPoketMonsterView::AssertValid() const
{
	CView::AssertValid();
}

void CPoketMonsterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPoketMonsterDoc* CPoketMonsterView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoketMonsterDoc)));
	return (CPoketMonsterDoc*)m_pDocument;
}
#endif //_DEBUG


// CPoketMonsterView 메시지 처리기


void CPoketMonsterView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_LEFT:
		m_cPlayer->setXLocation(-5, nChar);
		break;
	case VK_RIGHT:
		m_cPlayer->setXLocation(5, nChar);
		break;
	case VK_UP:
		m_cPlayer->setYLocation(-5, nChar);
		break;
	case VK_DOWN:
		m_cPlayer->setYLocation(5, nChar);
		break;
	default:
		break;
	}

	InvalidateRect(NULL, FALSE);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CPoketMonsterView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CPoketMonsterView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (1 == nIDEvent)
	{
		m_cPlayer->actionStep();
	}

	InvalidateRect(NULL, FALSE);

	CView::OnTimer(nIDEvent);
}


int CPoketMonsterView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CPaintDC dc(this);
	m_cPoketMonsterMap = new CPoketMonsterMap(&dc);
	m_cPlayer = new CPlayer(&dc);

	SetTimer(1, 100, NULL);

		return 0;
}
