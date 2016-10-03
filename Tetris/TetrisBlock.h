#pragma once
#include "TetrisMap.h"
#include "TetrisColor.h"
#include "TetrisImage.h"

#define TETRIS_PATSIZE 7
class CTetrisBlock : CTetrisColor
{
	int m_patindex; //block�� ���
	int m_dir; //block�� ȸ�� ����
	POINT m_pos; //���� ��ġ
	POINT m_nextBlock; //���� �������� ����
public:
	static POINT m_type[TETRIS_PATSIZE][4][4];
	CTetrisBlock(void);
	~CTetrisBlock(void);
	POINT getPos(void);
	int setPos(POINT pos);
	int getDir(void);
	int getPatIndex(void);
	void blockDraw(CTetrisImage* Image);
	int key(UINT nChar, int (*map)[MAP_W]);
	int checkBlockMove(int dir, int dx, int dy, int (*map)[MAP_W]);
	int getNextBlock(void);
};

