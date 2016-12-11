#include "stdafx.h"
#include "TetrisBGM.h"


CTetrisBGM::CTetrisBGM(void)
{
	m_aBgmPath.Add( _T("C:\\Users\\r00tlee\\Music\\∞ı≥Ï¿Ω±‚\\Tetris_main.wav") );
	m_aBgmPath.Add( _T("C:\\Users\\r00tlee\\Music\\∞ı≥Ï¿Ω±‚\\Tetris_GamePlay.wav") );

	playBGM(BGM_MAIN);
}


CTetrisBGM::~CTetrisBGM(void)
{
	m_aBgmPath.RemoveAll();
}


void CTetrisBGM::playBGM(int bgmNumber)
{
	if (bgmNumber <= m_aBgmPath.GetCount() )	PlaySound(m_aBgmPath.GetAt(bgmNumber), AfxGetInstanceHandle(),  SND_ASYNC | SND_LOOP);
}
