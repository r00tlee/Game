#include "stdafx.h"
#include "TetrisRoot.h"
#include "resource.h"

CTetrisRoot::CTetrisRoot(void)
{
	m_TetrisMap = new CTetrisMap();
	m_TetrisBlock = new CTetrisBlock();
	m_TetrisBGM = new CTetrisBGM();
	m_state = 0;
}


CTetrisRoot::~CTetrisRoot(void)
{
	delete m_TetrisMap;
	delete m_TetrisBlock;
	delete m_TetrisBGM;
	delete m_TetrisImage;
}

void CTetrisRoot::Draw(CDC* pDC)
{
	if (0 == m_state)
	{
		m_TetrisImage = new CTetrisImage(pDC);
		m_TetrisImage->m_bufCDC.StretchBlt(0, 0, 1360, 660, &(m_TetrisImage->m_aCDC[0]), 0, 0, 1920, 1080, SRCCOPY);
	}
	else
	{
		m_TetrisImage->m_bufCDC.BitBlt(0, 0, 1920, 1080, &(m_TetrisImage->m_aCDC[1]), 0, 0, SRCCOPY); //깨끗한 화면으로 시작
		m_TetrisMap->Draw(m_TetrisImage);
	  m_TetrisBlock->blockDraw(m_TetrisImage);
	}

	pDC->BitBlt(0, 0, 1920, 1080, &(m_TetrisImage->m_bufCDC), 0, 0, SRCCOPY);
}

int CTetrisRoot::key(UINT nChar)
{
	if (m_state == 0)
	{
		if (nChar == VK_SPACE)
		{
			m_state = 1;
			m_TetrisBGM->playBGM(BGM_PLAY);
		}
		
		return 0;
	}
	
	//키를 넘겨주기 위해선 block의 좌표를 넘겨줘야 한다.
	int state = m_TetrisBlock->key(nChar, m_TetrisMap->m_data);
	if (1 == state)
	{
		m_TetrisMap->copyToData(m_TetrisBlock->m_type, m_TetrisBlock->getPatIndex(), m_TetrisBlock->getDir(), m_TetrisBlock->getPos() );
		m_TetrisMap->sameBlock();
		m_TetrisBlock->getNextBlock();
	}

	return 0;
}
