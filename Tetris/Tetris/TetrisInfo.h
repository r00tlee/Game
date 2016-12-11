#pragma once
#include "TetrisColor.h"
#include "TetrisImage.h"
#include "Key.h"

#define TETRIS_PATSIZE 7

enum EMapSize
{
	MAP_W = 10 + 2,
	MAP_H = 20 + 2
};

enum EBlockShape
{
	MAP_WALL = 200,
	MAP_BLANK,
	MAP_TOP,
	MAP_BLOCK,
};

enum EBlockSize
{
	BlockSize = 35
};

class CTetrisInfo : public CKey
{
	int m_patindex; //block�� ���
	int m_dir; //block�� ȸ�� ����
	POINT m_pos; //���� ��ġ
	int m_shawdowPos; //���� ��ġ�� �׸��� ��ġ
	int m_nextPatindex;
	int m_nextDir;
	int m_map[MAP_H][MAP_W];
public:
	static POINT m_type[TETRIS_PATSIZE][4][4];
	CTetrisInfo(void);
	~CTetrisInfo(void);
	void Draw();
	int key(UINT nChar);
	int CheckBlockMove(int dir, int dx, int dy);
	void MoveToEnd(void);
	int MoveBlockDown(void);
	void CopyBlockToData(void);
	void GetNewBlock(void);
	void CheckSameBlock(void);
	void DownBlock(int y);
	void ShawDowBlock(void);
};

