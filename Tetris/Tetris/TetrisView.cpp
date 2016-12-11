
// TetrisView.cpp : CTetrisView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tetris.h"
#endif

#include "TetrisDoc.h"
#include "TetrisView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTetrisView

IMPLEMENT_DYNCREATE(CTetrisView, CView)

BEGIN_MESSAGE_MAP(CTetrisView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()


#include <iostream>
#include <list>
using namespace std;

//      Convenience Key Controller         //
struct S_KEY
{
   friend BOOL KeyController(int key, int hesitateToChainMove, int eachDelayDuringChainMove);
   friend void KeyCompulsionController(int key, int hesitateToChainMove, int eachDelayDuringChainMove);

private:

   int key;
   int hesitate;
   int delay;
   bool press;
};
list<S_KEY> g_libYS_keySet;

BOOL KeyController(int key, int hesitateToChainMove, int eachDelayDuringChainMove)
{
   list<S_KEY>::iterator it;

   for(it = g_libYS_keySet.begin(); it != g_libYS_keySet.end(); it++)
   {
      if(key == it->key)   break;
   }
   if(g_libYS_keySet.end() == it)
   {
      S_KEY set;
      set.key = key;
      set.hesitate = hesitateToChainMove;
      set.delay = 0;
      set.press = false;

      g_libYS_keySet.push_back(set);
      it = --g_libYS_keySet.end();
   }

   
   if(GetAsyncKeyState(key) & 0x8000)
   {
      if(false == it->press)
      {
         it->press = true;
         return TRUE;
      }
      else
      {
         if(0 != it->hesitate)   it->hesitate--;
         else
         {
            if(0 != it->delay)   it->delay--;
            else
            {
               it->delay = eachDelayDuringChainMove;
               return TRUE;
            }
         }
      }
   }
   else
   {
      if(true == it->press)
      {
         it->press = false;
         it->hesitate = hesitateToChainMove;
      }
   }

   return FALSE;
}
void KeyCompulsionController(int key, int hesitateToChainMove, int eachDelayDuringChainMove)
{
   list<S_KEY>::iterator it;

   for(it = g_libYS_keySet.begin(); it != g_libYS_keySet.end(); it++)
   {
      if(key == it->key)   break;
   }
   if(g_libYS_keySet.end() == it)
   {
      S_KEY set;
      set.key = key;
      set.hesitate = hesitateToChainMove;
      set.delay = 0;
      set.press = false;

      g_libYS_keySet.push_back(set);
      it = --g_libYS_keySet.end();
   }

   it->hesitate = hesitateToChainMove;
   it->delay = eachDelayDuringChainMove;
}

void DestroyKeyController()
{
   g_libYS_keySet.clear();
}

// CTetrisView ����/�Ҹ�

CTetrisView::CTetrisView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CTetrisView::~CTetrisView()
{
	delete g_CTetrisImage;
	delete m_CTetrisInfo;
	delete m_CTetrisBGM;
}

BOOL CTetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CTetrisView �׸���

void CTetrisView::OnDraw(CDC* pDC)
{
	CTetrisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	if (0 == m_state)
	{
		g_CTetrisImage->m_bufCDC.StretchBlt(0, 0, 1360, 660, &(g_CTetrisImage->m_aCDC[0]), 0, 0, 1920, 1080, SRCCOPY);
	}
	else
	{
		g_CTetrisImage->m_bufCDC.BitBlt(0, 0, 1920, 1080, &(g_CTetrisImage->m_aCDC[1]), 0, 0, SRCCOPY); //������ ȭ������ ����
	  m_CTetrisInfo->Draw();
	}

	pDC->BitBlt(0, 0, 1920, 1080, &(g_CTetrisImage->m_bufCDC), 0, 0, SRCCOPY);
}


// CTetrisView �μ�

BOOL CTetrisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTetrisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTetrisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CTetrisView ����

#ifdef _DEBUG
void CTetrisView::AssertValid() const
{
	CView::AssertValid();
}

void CTetrisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetrisDoc* CTetrisView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisDoc)));
	return (CTetrisDoc*)m_pDocument;
}
#endif //_DEBUG


// CTetrisView �޽��� ó����


int CTetrisView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	g_CTetrisImage = new CTetrisImage(&dc);
	m_CTetrisInfo  = new CTetrisInfo();
	m_CTetrisBGM   = new CTetrisBGM();

	SetTimer(1, 1000, NULL);
	SetTimer(2, 0, NULL);
	m_state = 0;

		return 0;
}

void CTetrisView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (0 == m_state) return;

	if (1 == nIDEvent) m_state = m_CTetrisInfo->key(VK_DOWN);
	else if (2 == nIDEvent)
	{		
		if ( KeyController(VK_UP,    25,  5) ) m_state = m_CTetrisInfo->key(VK_UP);
		if ( KeyController(VK_DOWN,   5,  2) ) m_state = m_CTetrisInfo->key(VK_DOWN);
		if ( KeyController(VK_LEFT,   7,  1) ) m_state = m_CTetrisInfo->key(VK_LEFT);
		if ( KeyController(VK_RIGHT,  7,  1) ) m_state = m_CTetrisInfo->key(VK_RIGHT);
  	if ( KeyController(VK_SPACE, 50, 10) ) m_state = m_CTetrisInfo->key(VK_SPACE);
	}

	Invalidate(FALSE);

	if (-1 == m_state)
	{
		KillTimer(1);
		KillTimer(2);
		MessageBox(_T("Game Over"), _T("Tetris"), NULL);
	}

	CView::OnTimer(nIDEvent);
}


void CTetrisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (0 == m_state)
	{
		if (nChar == VK_SPACE)
		{
			m_state = 1;
			m_CTetrisBGM->playBGM(BGM_PLAY);
			Sleep(300);
		}
	}

	m_CTetrisInfo->KeyDown(nChar);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CTetrisView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_CTetrisInfo->KeyUP(nChar);
	if ( m_CTetrisInfo->KeyClearCheck() )	DestroyKeyController();
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
