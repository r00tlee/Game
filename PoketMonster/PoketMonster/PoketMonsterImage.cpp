#include "stdafx.h"
#include "PoketMonsterImage.h"
#include "resource.h"

CDC CPoketMonsterImage::m_aCDC[10];
CDC CPoketMonsterImage::m_bufCDC;

CPoketMonsterImage::CPoketMonsterImage(CDC* pDC)
{
	if (NULL != m_bufCDC)
	{
		return;
	}

	m_bufBitmap.CreateCompatibleBitmap(pDC, 1920, 1080);
	m_bufCDC.CreateCompatibleDC(pDC);
	m_bufCDC.SelectObject(&m_bufBitmap);

	for (int i=0; i<IMG_MAX; i++)
	{
		m_aBitmap[i].LoadBitmapW(IDB_BITMAP1+i);
		m_aCDC[i].CreateCompatibleDC(pDC);
		m_aCDC[i].SelectObject(&m_aBitmap[i]);
	}
}

CPoketMonsterImage::~CPoketMonsterImage(void)
{
	for (int i=0; i<IMG_MAX; i++)
	{
		DeleteDC(m_aCDC[i].m_hDC);
		DeleteObject(m_aBitmap[i]);
	}
}