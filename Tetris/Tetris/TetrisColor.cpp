#include "stdafx.h"
#include "TetrisColor.h"


CTetrisColor::CTetrisColor(void)
{
	m_aBrush.Add( CreateSolidBrush(RGB(2, 163, 227)) );   //ÇÏ´Ã
	m_aBrush.Add( CreateSolidBrush(RGB(254, 213, 39)) );  //³ë¶û
	m_aBrush.Add( CreateSolidBrush(RGB(38, 159, 20)) );   //ÃÊ·Ï
	m_aBrush.Add( CreateSolidBrush(RGB(240, 48, 32)) );   //»¡°­
	m_aBrush.Add( CreateSolidBrush(RGB(14, 66, 234)) );   //ÆÄ¶û
	m_aBrush.Add( CreateSolidBrush(RGB(255, 95, 5)) );    //ÁÖÈ²
	m_aBrush.Add( CreateSolidBrush(RGB(137, 53, 241)) );  //º¸¶ó
	m_aBrush.Add( CreateSolidBrush(RGB(255, 255, 255)) ); //Èò»ö
}

CTetrisColor::~CTetrisColor(void)
{
	for (int i=0; i<m_aBrush.GetCount(); i++)
		DeleteObject(m_aBrush.GetAt(i) );
	m_aBrush.RemoveAll();
}
