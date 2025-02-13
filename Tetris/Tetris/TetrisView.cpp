
// TetrisView.cpp : CTetrisView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CTetrisView 생성/소멸

CTetrisView::CTetrisView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CTetrisView::~CTetrisView()
{
	delete g_CTetrisImage;
	delete m_CTetrisInfo;
	delete m_CTetrisBGM;
}

BOOL CTetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTetrisView 그리기

void CTetrisView::OnDraw(CDC* pDC)
{
	CTetrisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	if (0 == m_state)
	{
		g_CTetrisImage->m_bufCDC.StretchBlt(0, 0, 1360, 660, &(g_CTetrisImage->m_aCDC[0]), 0, 0, 1920, 1080, SRCCOPY);
	}
	else
	{
		g_CTetrisImage->m_bufCDC.BitBlt(0, 0, 1920, 1080, &(g_CTetrisImage->m_aCDC[1]), 0, 0, SRCCOPY); //깨끗한 화면으로 시작
	  m_CTetrisInfo->Draw();
	}

	pDC->BitBlt(0, 0, 1920, 1080, &(g_CTetrisImage->m_bufCDC), 0, 0, SRCCOPY);
}


// CTetrisView 인쇄

BOOL CTetrisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTetrisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTetrisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CTetrisView 진단

#ifdef _DEBUG
void CTetrisView::AssertValid() const
{
	CView::AssertValid();
}

void CTetrisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetrisDoc* CTetrisView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisDoc)));
	return (CTetrisDoc*)m_pDocument;
}
#endif //_DEBUG


// CTetrisView 메시지 처리기


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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_CTetrisInfo->KeyUP(nChar);
	if ( m_CTetrisInfo->KeyClearCheck() )	DestroyKeyController();
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
