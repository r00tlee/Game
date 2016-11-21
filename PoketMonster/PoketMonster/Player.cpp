#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer(CDC* pDC)
	: m_AniSize(2), CPoketMonsterImage(pDC), CPoketMonsterMap(pDC)
{
	m_location.x = 50;
	m_location.y = 50;
	m_ImageIndex = 0;
	m_ActionState = FALSE;
#ifdef _DEBUG
	m_ForestState = FALSE;
#endif
}


CPlayer::~CPlayer(void)
{
}


int CPlayer::getXLocation(void)
{
	return m_location.x;
}


int CPlayer::getYLocation(void)
{
	return m_location.y;
}

void CPlayer::setXLocation(int x, int locationState)
{
	m_locationState = locationState;
	m_location.x = m_location.x + x;
	m_ActionState = TRUE;

	int dx = m_location.x / 100;
	int dy = m_location.y / 100;

#ifdef _DEBUG
	if ( '1' == m_aMap[dy][dx] )
	{
		m_ForestState = TRUE;
	}
#endif
}


void CPlayer::setYLocation(int y, int locationState)
{
	m_locationState = locationState;
	m_location.y = m_location.y + y;
	m_ActionState = TRUE;

	int dx = m_location.x / 100;
	int dy = m_location.y / 100;

#ifdef _DEBUG
	if ( '1' == m_aMap[dy][dx] )
	{
		m_ForestState = TRUE;
	}
#endif
}


void CPlayer::Draw(void)
{
	switch(m_locationState)
	{
	case VK_UP:
		m_bufCDC.StretchBlt(m_location.x, m_location.y, 200/2, (m_ImageIndex+1)*(200/2), &m_aCDC[0], 0, m_ImageIndex*200, 200, (m_ImageIndex+1)*200, SRCCOPY);
		locationPrint();
		break;
	case VK_DOWN:
		m_bufCDC.StretchBlt(m_location.x, m_location.y, 200/2, (m_ImageIndex+1)*(200/2), &m_aCDC[1], 0, m_ImageIndex*200, 200, (m_ImageIndex+1)*200, SRCCOPY);
    locationPrint();
		break;
	case VK_LEFT:
		m_bufCDC.StretchBlt(m_location.x, m_location.y, 200/2, (m_ImageIndex+1)*(200/2), &m_aCDC[2], 0, m_ImageIndex*200, 200, (m_ImageIndex+1)*200, SRCCOPY);
    locationPrint();
		break;
	case VK_RIGHT:
		m_bufCDC.StretchBlt(m_location.x, m_location.y, 200/2, (m_ImageIndex+1)*(200/2), &m_aCDC[3], 0, m_ImageIndex*200, 200, (m_ImageIndex+1)*200, SRCCOPY);
		locationPrint();
		break;
	default:
		break;
	}
}


void CPlayer::actionStep(void)
{
	if (m_ActionState)
	{
		m_ImageIndex++;
	  if (m_AniSize <= m_ImageIndex)
	  {
		  m_ImageIndex = 0;
			m_ActionState = FALSE;
	  }
	}
}

void CPlayer::locationPrint(void)
{
#ifdef _DEBUG
	m_prlocation.Format(_T("[x : %d] [y : %d] [ index : [%d][%d] ]"), m_location.x, m_location.y, m_location.y/100, m_location.x/100, m_ImageIndex);
	m_bufCDC.TextOutW(m_location.x, m_location.y, m_prlocation );

	if (m_ForestState)
	{
		m_bufCDC.TextOutW(m_location.x, m_location.y-30, _T("Ç®½£") );
		m_ForestState = FALSE;
	}
#endif
}
