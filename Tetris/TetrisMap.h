#pragma once
#include "TetrisColor.h"
#include "TetrisImage.h"

enum EMapSize
{
	MAP_W = 10 + 2,
	MAP_H = 20 + 2
};

enum EBlockShape
{
	MAP_WALL = 200,
	MAP_BLANK,
	MAP_TOP
};

enum EBlockSize
{
	BlockSize = 35
};

class CTetrisMap : CTetrisColor
{
public:
	int m_data[MAP_H][MAP_W];

	CTetrisMap(void);
	~CTetrisMap(void);
	void Draw(CTetrisImage* Image); //¸Ê Ãâ·Â
	int copyToData(POINT (*type)[4][4], int patIndex, int dir, POINT pos);
	int sameBlock(void);
	int lineClearCheck(int y);
	int lineClear(int y);
};

