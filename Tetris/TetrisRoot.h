#pragma once
#include "TetrisMap.h"
#include "TetrisBlock.h"
#include "TetrisBGM.h"
#include "TetrisImage.h"

class CTetrisRoot
{
	CTetrisMap* m_TetrisMap;
	CTetrisBlock* m_TetrisBlock;
	CTetrisBGM* m_TetrisBGM;
	CTetrisImage* m_TetrisImage;
	BITMAP m_Bit;
	int m_state;
public:
	CTetrisRoot(void);
	~CTetrisRoot(void);
	void Draw(CDC* pDC); //ȭ�� ���
	int key(UINT nChar); //Ű���� ���
};

