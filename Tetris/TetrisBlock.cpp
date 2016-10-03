#include "stdafx.h"
#include "TetrisBlock.h"
#include "TetrisMap.h"
#include <time.h>

POINT CTetrisBlock::m_type[TETRIS_PATSIZE][4][4]={
	{	//■■■■
		{0,0,1,0,2,0,3,0},
		{0,0,0,1,0,2,0,3},
		{0,0,1,0,2,0,3,0},
		{0,0,0,1,0,2,0,3}
	},
	{	//■■
		//■■
		{0,0,1,0,0,1,1,1},
		{0,0,1,0,0,1,1,1},
		{0,0,1,0,0,1,1,1},
		{0,0,1,0,0,1,1,1}
	},
	{	//  ■■
		//■■		
		{2,0,1,0,1,1,0,1},
		{0,0,0,1,1,1,1,2},
		{2,0,1,0,1,1,0,1},
		{0,0,0,1,1,1,1,2}
	},
	{	//■■
		//  ■■
		{0,0,1,0,1,1,2,1},
		{1,0,1,1,0,1,0,2},
		{0,0,1,0,1,1,2,1},
		{1,0,1,1,0,1,0,2}
	},
	{	//■
		//■■■		
		{0,0,0,1,1,1,2,1},
		{1,0,0,0,0,1,0,2},
		{0,0,1,0,2,0,2,1},
		{1,0,1,1,1,2,0,2}
	},
	{	//　　■
		//■■■
		{2,0,2,1,1,1,0,1},
		{0,0,0,1,0,2,1,2},
		{2,0,1,0,0,0,0,1},
		{0,0,1,0,1,1,1,2}
	}
	,
	{	//  ■
		//■■■
		{1,0,0,1,1,1,2,1},
		{0,0,0,1,0,2,1,1},
		{0,0,1,0,2,0,1,1},
		{0,1,1,0,1,1,1,2}
	}
}; //떨어지는 블록 패턴


CTetrisBlock::CTetrisBlock(void)
{
	srand(time(NULL));
	m_patindex = rand() % TETRIS_PATSIZE;
	m_dir = rand() % 4;
	m_pos.x = 4;
	m_pos.y = 0;

	m_nextBlock.x = rand() % 7;
	m_nextBlock.y = 0;
}

CTetrisBlock::~CTetrisBlock(void)
{
}

POINT CTetrisBlock::getPos(void)
{
	return m_pos;
}


int CTetrisBlock::setPos(POINT pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	return 0;
}


int CTetrisBlock::getDir(void)
{
	return m_dir;
}


int CTetrisBlock::getPatIndex(void)
{
	return m_patindex;
}


void CTetrisBlock::blockDraw(CTetrisImage* Image)
{
	int x = 0;
	int y = 0;

	for(int i=0; i<4; i++)
	{
		x = m_pos.x + m_type[m_patindex][m_dir][i].x;
		y = m_pos.y + m_type[m_patindex][m_dir][i].y;
		
		x = BlockSize * x;
		y = BlockSize * y;
		Image->m_bufCDC.StretchBlt(x, y, 35, 35, &(Image->m_aCDC[m_patindex+2]), 0, 0, 35, 35, SRCCOPY);
	}

	//다음 블럭 미리보기
	for(int i=0; i<4; i++)
	{
		x = 15 + m_type[m_nextBlock.x][m_nextBlock.y][i].x;
		y = 5 + m_type[m_nextBlock.x][m_nextBlock.y][i].y;
		
		x = BlockSize * x;
		y = BlockSize * y;
		Image->m_bufCDC.StretchBlt(x, y, 35, 35, &(Image->m_aCDC[m_nextBlock.x+2]), 0, 0, 35, 35, SRCCOPY);
	}
}

int CTetrisBlock::key(UINT nChar, int (*map)[MAP_W])
{
	if (nChar == VK_UP)
	{
 		int dir = m_dir;
		if (3 < dir+1) dir = 0;
		else dir += 1;

		if (0 == checkBlockMove(dir, m_pos.x, m_pos.y, map))  m_dir = dir;
	}
	else if (nChar == VK_DOWN)
	{
		if (0 == checkBlockMove(m_dir, m_pos.x, m_pos.y+1, map))  m_pos.y += 1;
		else return 1;
	}
	else if (nChar == VK_LEFT)
	{
		if (0 == checkBlockMove(m_dir, m_pos.x-1, m_pos.y, map))  m_pos.x -= 1;
	}
	else if (nChar == VK_RIGHT)
	{
		if (0 == checkBlockMove(m_dir, m_pos.x+1, m_pos.y, map))  m_pos.x += 1;
	}
	else if (nChar == VK_SPACE)
	{
		while (!checkBlockMove(m_dir, m_pos.x, m_pos.y+1, map))
		{
			m_pos.y += 1;
		}
		return 1;
	}
		
	return 0;
}


int CTetrisBlock::checkBlockMove(int dir, int dx, int dy, int (*map)[MAP_W])
{
	int x, y;

	for (int i=0; i<4; i++)
	{
		x = dx + m_type[m_patindex][dir][i].x;
		y = dy + m_type[m_patindex][dir][i].y;

		if (MAP_BLANK != map[y][x]
		 && MAP_TOP != map[y][x] )
		{
			return -1;
		}
	}

	return 0;
}


int CTetrisBlock::getNextBlock(void)
{
	m_pos.x = 4;
	m_pos.y = 1;
	m_patindex = m_nextBlock.x;
	m_dir = m_nextBlock.y;

	m_nextBlock.x = rand() % TETRIS_PATSIZE;
	m_nextBlock.y = 0;

	return 0;
}
