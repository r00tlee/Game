#pragma once
#define IMG_MAX 5
class CPoketMonsterImage
{
	CBitmap m_bufBitmap;
	CBitmap m_aBitmap[10];
public:
	static CDC  m_bufCDC;
	static CDC  m_aCDC[10];
	CPoketMonsterImage(CDC* pDC);
	~CPoketMonsterImage(void);
};

