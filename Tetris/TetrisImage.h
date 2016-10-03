#pragma once
class CTetrisImage
{
	CBitmap m_bufBitmap;
	CBitmap m_aBitmap[10];
public:
	CDC  m_bufCDC;
	CDC  m_aCDC[10];
	CTetrisImage(CDC* pDC);
	~CTetrisImage(void);
};

