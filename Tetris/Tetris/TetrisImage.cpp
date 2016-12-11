#include "stdafx.h"
#include "TetrisImage.h"
#include "resource.h"

CTetrisImage* g_CTetrisImage;

CTetrisImage::CTetrisImage(CDC* pDC)
{
	m_bufBitmap.CreateCompatibleBitmap(pDC, 1920, 1080);
	m_bufCDC.CreateCompatibleDC(pDC);
	m_bufCDC.SelectObject(&m_bufBitmap);

	for (int i=0; i<9; i++)
	{
		m_aBitmap[i].LoadBitmapW(IDB_BITMAP1+i);
		m_aCDC[i].CreateCompatibleDC(pDC);
		m_aCDC[i].SelectObject(&m_aBitmap[i]);
	}

	m_bf.BlendOp = AC_SRC_OVER;
	m_bf.BlendFlags = 0;
	m_bf.SourceConstantAlpha = 50;
	m_bf.AlphaFormat = 0;
}


CTetrisImage::~CTetrisImage(void)
{
	for (int i=0; i<8; i++)
	{
		DeleteDC(m_aCDC[i].m_hDC);
		DeleteObject(m_aBitmap[i]);
	}
	DeleteDC(m_bufCDC);
	DeleteObject(m_bufBitmap);
}