
// PoketMonsterView.cpp : CPoketMonsterView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CPoketMonsterView ����/�Ҹ�

CPoketMonsterView::CPoketMonsterView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CPoketMonsterView::~CPoketMonsterView()
{
	delete m_cPlayer;
	delete m_cPoketMonsterMap;
}

BOOL CPoketMonsterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CPoketMonsterView �׸���

void CPoketMonsterView::OnDraw(CDC* pDC)
{
	CPoketMonsterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	m_cPoketMonsterMap->Draw();
	m_cPlayer->Draw();
	pDC->BitBlt(0, 0, 1920, 1080, &(m_cPlayer->m_bufCDC), 0, 0, SRCCOPY);
}

// CPoketMonsterView �μ�

BOOL CPoketMonsterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CPoketMonsterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CPoketMonsterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CPoketMonsterView ����

#ifdef _DEBUG
void CPoketMonsterView::AssertValid() const
{
	CView::AssertValid();
}

void CPoketMonsterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPoketMonsterDoc* CPoketMonsterView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoketMonsterDoc)));
	return (CPoketMonsterDoc*)m_pDocument;
}
#endif //_DEBUG


// CPoketMonsterView �޽��� ó����


void CPoketMonsterView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CPoketMonsterView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
